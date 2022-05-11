#pragma once
#include "ArrayOperations.h"
#include <Arduino.h>
namespace Measure
{
    
    template <typename T> inline T TakeGroup(
        T* InputArray,
        const size_t MeasuresPerBlock, 
        T (*TakeMeasure)() = NULL,
        unsigned long _delay = 5) 
    {
        bool bAllocated = false;
        if (!TakeMeasure)
            return (T)(NULL);
        if (!InputArray)
        {
            InputArray = (T*)malloc(sizeof(T) * MeasuresPerBlock);
            if (!InputArray)
                return TakeMeasure();
            bAllocated = true;
        }
        for (int i = 0; i < MeasuresPerBlock; i++)
        {
            InputArray[i] = TakeMeasure();
            delay(_delay);
        }
        ShellSort<T>(InputArray, 0, MeasuresPerBlock);
        T t = (T)(NULL);
        if (MeasuresPerBlock > 6) {
            const size_t MeasuresPerBlockMinusThree = MeasuresPerBlock - 3;
            const size_t MeasuresPerBlockMinusSix = MeasuresPerBlock - 6;
            for (int i = 3; i < MeasuresPerBlockMinusThree; i++)
            {//We exclude the first three and the last three
                t += InputArray[i] / MeasuresPerBlockMinusSix;
            }
        } else {
            for (int i = 0; i < MeasuresPerBlock; i++)
            {
                t += InputArray[i] / MeasuresPerBlock;
            }
        }
        if (bAllocated) {
            free(InputArray);
        }
        return t;
  }
    template <typename T> inline String DrawGraph(
        T* Array,
        size_t Size
    ) {
        if (Size == 0 || Size % 5 != 0) {
            return "Invalid array Size!";
        }
        if (!Array) {
            return "Invalid Array!";
        }
        ShellSort<T>(Array, 0, Size);
        T Graph[] = {
            Average<T>(Array, 0,            Size / 5),
            Average<T>(Array, Size / 5,     Size / 5),
            Average<T>(Array, Size / 5 * 2, Size / 5),
            Average<T>(Array, Size / 5 * 3, Size / 5),
            Average<T>(Array, Size / 5 * 4, Size / 5)
        };
        if (Graph[4] == Graph[0]) {//horizontal line
            return "Data could not be displayed!";
        }
        T Span = Graph[4] - Graph[0];
        int timesMultiplied = 0;
        while (abs(Span) < 0.1)
        {
            timesMultiplied++;
            for (int i = 0; i < 5; i++)
            {
                Graph[i] *= (T)10;
            }
            Span = Graph[4] - Graph[0];
        }
        int DataDisplay[5];
        for (int i = 0; i < 5; i++)
        {
            T Height = Map<T>(Graph[i], Graph[0], Graph[4], 1, 5);
            DataDisplay[i] = round(Height);//typename T becomes int
            DataDisplay[i] = 5 - DataDisplay[i];
        }
        String CharMatrix[8];
        for (int i = 0; i < 8; i++) {
            CharMatrix[i] = "";
        }
        CharMatrix[0] = "^";
        CharMatrix[6] = "@-";
        CharMatrix[7] = " ";
        for (int i = 1; i < 6; i++)
        {
            CharMatrix[i] += "| ";
            for (int j = 0; j < 5; j++)
            {
                if (i - 1 >= DataDisplay[j]) {
                    CharMatrix[i] += "#######";
                } else {
                    CharMatrix[i] += "       ";
                }
            }
        }
        T mult = (T)pow(10, -timesMultiplied);
        char ToPrintVolt[6];
        for (int i = 0; i < 5; i++)
        {
            Graph[i] *= mult;
            memset(ToPrintVolt, 0, 6);
            CharMatrix[6] += "-------";
            dtostrf(Graph[i], 5, 3, ToPrintVolt);
            CharMatrix[7] += " ";
            CharMatrix[7] += ToPrintVolt;
            CharMatrix[7] += " ";
        }
        CharMatrix[6] += ">";
        String Final;
        for (int i = 0; i < 8; i++)
        {
            Final += CharMatrix[i] + '\n';
            CharMatrix[i] = "";//We relase the space as soon as we can
        }
        return Final;
    }
}
