# TELNET (TEletype NETwork)
[ref](https://www.rfc-editor.org/rfc/rfc854.html)
Commands are identified by a prefix character Interpretet As Command (IAC) with code 255.

## Structure
IAC - COMMAND CODE - OPTION CODE

### Command code
WILL (251) - Accepting a request to enable
WON'T (252) - Rejecting a request to enable or accepting a request to disable
DO (253) - Approving request to enable or requesting to enable
DON'T (254) - Disapproving a request to enable or approving an offer to disable or requesting to disable

### Common options
0 (Binary) - It interpret as 8-bit binary transmission
1	(Echo) - It will echo the data that received on one side to the other side
3	(Suppress go ahead) -	It will suppress go ahead signal after data
5	(Status) -	It will request for the status of TELNET
6 (Timing mark) -	It define the timing marks
8	(Line width) -	It specifies the line width
9	(Page size) -	It specifies the number of lines in a page
24	(Terminal type) -	It set the terminal type
32	(Terminal speed) -	It set the terminal speed
34	(Line mode) - It will change to the line mode

