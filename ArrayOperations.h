#pragma once
//ShellSort is a fast algorithm that doesn't base itself on recursion,
//recursion can cause crashes on the Arduino board by allocating too much memory
template <typename T> inline void ShellSort(T* arr, size_t since, size_t to,
  bool (*compare)(T a, T b) = [](T a, T b) {return (a > b); },
  void (*assign)(T& a, const T& b) = [](T& a, const T& b) { a = b; })
{
  for (size_t gap = (to - since) / 2U; gap > 0; gap /= 2U)
  {
    for (size_t i = gap + since; i < to; i++)
    {
      T temp = arr[i];
      size_t j = i;
      for (; j >= (gap + since) && compare(arr[j - gap], temp); j -= gap)
      {
        assign(arr[j], arr[j - gap]);
      }
      assign(arr[j], temp);
    }
  }
}
//Calculates the average value of a set, you can set the start and the end element
template <typename T> inline T Average(const T* arr, size_t start, size_t count)
{
    T t = arr[start] / count;
    for (size_t i = 1; i < count; i++) {//Start at 1 since first element was already considered
        t += arr[start + i] / count;//Longer, but important to prevent overflow
    }
    return t;
}
/**
 * @brief Generalization of map() function, same body
 * 
 * @tparam T the unit type (int/uint/float/double)
 * @param x 
 * @param in_min 
 * @param in_max 
 * @param out_min 
 * @param out_max 
 * @return T 
 */
template <typename T> inline T Map(T x, T in_min, T in_max, T out_min, T out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline String ReplaceInString(const String& s, char toReplace, char replaceWith)
{
  String copy = s;
  copy.replace(toReplace, replaceWith);
  return copy;
}
