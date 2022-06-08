#pragma once
//  Languages/Italian.h
//  Text for compiling and later running the program in Italian, 
//  a correction to pint the number with a comma instead of a dot is added.

#define REMINDER "Digita \"LEGGI\", \"CALIBRA\" o \"MULTIPLA\" per iniziare..."
#define CALIBRATE "Digita \"FINE\" per terminare la calibrazione..."

#define SETUP_COMPLETED "Setup completato."

#define BEST_VALUE "Miglio valore: "

#define MEASURING "Misurando..."

#define OF " di "

#define GROUP_RESULT "Valori finali:"

#define WAIT_FOR_GO "Digita \"VAI\" per effettuare la prossima misura \"FINE\" per interrompere..."

#define READ_UPPER "LEGGI"
#define READ_LOWER "leggi"

#define MULTIPLE_UPPER "MULTIPLA"
#define MULTIPLE_LOWER "multipla"

#define CALIBRATE_UPPER "CALIBRA"
#define CALIBRATE_LOWER "calibra"

#define END_UPPER "FINE"
#define END_LOWER "fine"

#define GO_UPPER "VAI"
#define GO_LOWER "vai"

#define PRINT_NUMBER(num) ReplaceInString(String(num, 4), '.', ',')