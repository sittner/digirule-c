# digirule-c

This is a C version of the [DigiRule](http://www.bradsprojects.com/the-digirule) firmware.
Please use Microchip's XC8 Compiler to build this.

## Enhancements

* structured in sub modules for each function
* fixed cycle time (1ms) for simpler handling of timing stuff
* dynamic POV message length to save memory
* added decimal version of dice
* use of controller's sleep and idle mode to save battery
* auto shut-off when not used
* mode selection without requirement of powercycle

## Usage

The software should just behave like the original one, except:

* Mode selection is not done by holding LogicInputA on power up but longer than 2 sec on normal operation
* Mode selector does not allow invalid modes
* LogicInputB could be hold >2 sec to go to sleep mode.
* If not used >60 sec device will go to sleep
* LogicInputA will wake up from sleep
* added mode 10 for decimal dice

