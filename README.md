# GURPS Evolution Readme
## Description
This code uses the GURPS role play system in an evolutionary program to create animals or monsters. The list of animals is in a .csv file.

## Algorithm
The General Algorithm is as follows.

1. Birth Babies
1. Mutate Babies
1. Make Babies Fight
1. Check Scores And Pick The Top Three Winners.
1. Record Baby Stats In .csv File
1. Cull The Losers
1. Repeat X Number Of Times

## Header File and Class Name Acronyms
In no particular order

* Evo = Main Evolution Program
* Glob = Global Values
* Rec = Recorder
* Ref = Referee
* pred_rnd.csv = Static Random Values For Unit Testing Preditors
* prey_rnd.csv = Static Random Values For Unit Testing Prey

The other files are named well.
