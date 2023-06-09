This atomic model dial a number and ring callee for a certain period of time. If callee picks up the phone, then it connect caller and callee. If not, then it abort ring and generate output to dirlinelookup module to make line free. 

Model file : dialing.cm
Event file : dialing.ev
Script to run : run_dialing.bat
Input: num, callee_pickup
Outputs: error, out, connect
