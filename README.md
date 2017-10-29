/***
 *      ____             _ _        _               _    _                          __ _                          
 *     / ___| _ __   ___| | |   ___| |__   ___  ___| | _(_)_ __   __ _   ___  ___  / _| |___      ____ _ _ __ ___ 
 *     \___ \| '_ \ / _ \ | |  / __| '_ \ / _ \/ __| |/ / | '_ \ / _` | / __|/ _ \| |_| __\ \ /\ / / _` | '__/ _ \
 *      ___) | |_) |  __/ | | | (__| | | |  __/ (__|   <| | | | | (_| | \__ \ (_) |  _| |_ \ V  V / (_| | | |  __/
 *     |____/| .__/ \___|_|_|  \___|_| |_|\___|\___|_|\_\_|_| |_|\__, | |___/\___/|_|  \__| \_/\_/ \__,_|_|  \___|
 *           |_|                                                 |___/                                            
 */
 Author: Ovidiu-Andrei Radulescu
 
 SUMMARY:
 The spell tool outputs words that are not included in the supplied "dictionary.txt" file.
 The program must be built using the supplied makefile or by using the command: cl spell.c dictionary_search.c
 The software must be used by writing the name of the program "spell" followed (or not) by arguments:
 -i filename.txt ->for specifying an input file.
 -o filename.txt ->for specifying an output file.
 -c ->specifies that the user wants to ignore cases.
 If no arguments are specified the default settings will be applied accordingly.
 Example:
 spell -i single_words_test.txt -c
 Will return:
 **********************
 *                    *
 *   Spell Checking   *
 *      Software      *
 *                    *
 *  Andrei Radulescu  *
 *                    *
 **********************

 Console shall be used for output
 word: operatingg               line: 15
 word: insspiration             line: 46
 word: writtten         	line: 68
 
 Tool chain used for building: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24215.1 for x86
 
 
