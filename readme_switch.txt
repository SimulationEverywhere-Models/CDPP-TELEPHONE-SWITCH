This is whole integerated model of telephone switch, which uses  following atomice 
models
1- TouchTone
2- DialTone (Phone)
3- HangUp (Phone)
4- PickUp (Phone)
5- Dialer (couple model of DirLineLookup couple model and Dialing atmomic 
model, where as DirLineLookup is couple model of DirLookup and Line Controller)

Model file : switch.cm
Event file : switch.ev
Script to run: run_switch.bat
Input: key_in caller_pickup hangup_in callee_
Outputs: pickuperror connect dial_out
