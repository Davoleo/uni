
�
Command: %s
1870*	planAhead2�
�read_checkpoint -auto_incremental -incremental C:/Dev/uni/master/II/Lab2/Lab1.srcs/utils_1/imports/synth_1/blinker_v2_pulsegen.dcpZ12-2866h px� 
�
;Read reference checkpoint from %s for incremental synthesis3154*	planAhead2U
SC:/Dev/uni/master/II/Lab2/Lab1.srcs/utils_1/imports/synth_1/blinker_v2_pulsegen.dcpZ12-5825h px� 
T
-Please ensure there are no constraint changes3725*	planAheadZ12-7989h px� 
e
Command: %s
53*	vivadotcl24
2synth_design -top blinker_v2 -part xc7s25csga225-1Z4-113h px� 
:
Starting synth_design
149*	vivadotclZ4-321h px� 
y
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2
	Synthesis2
xc7s25Z17-347h px� 
i
0Got license for feature '%s' and/or device '%s'
310*common2
	Synthesis2
xc7s25Z17-349h px� 
D
Loading part %s157*device2
xc7s25csga225-1Z21-403h px� 
o
HMultithreading enabled for synth_design using a maximum of %s processes.4828*oasys2
2Z8-7079h px� 
a
?Launching helper process for spawning children vivado processes4827*oasysZ8-7078h px� 
N
#Helper process launched with PID %s4824*oasys2
20672Z8-7075h px� 
�
%s*synth2z
xStarting RTL Elaboration : Time (s): cpu = 00:00:05 ; elapsed = 00:00:05 . Memory (MB): peak = 928.641 ; gain = 464.207
h px� 
�
synthesizing module '%s'638*oasys2

blinker_v22O
KC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2.vhd2
218@Z8-638h px� 
�
Hmodule '%s' declared at '%s:%s' bound to instance '%s' of component '%s'3392*oasys2
blinker_v2_pulsegen2V
TC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_pulsegen.vhd2
342
dut_pulsegen2
blinker_v2_pulsegen2O
KC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2.vhd2
408@Z8-3491h px� 
�
synthesizing module '%s'638*oasys2
blinker_v2_pulsegen2X
TC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_pulsegen.vhd2
408@Z8-638h px� 
�
Hmodule '%s' declared at '%s:%s' bound to instance '%s' of component '%s'3392*oasys2
blinker_v2_FFRE2R
PC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_FFRE.vhd2
342
ff02
blinker_v2_FFRE2X
TC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_pulsegen.vhd2
538@Z8-3491h px� 
�
synthesizing module '%s'638*oasys2
blinker_v2_FFRE2T
PC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_FFRE.vhd2
418@Z8-638h px� 
�
%done synthesizing module '%s' (%s#%s)256*oasys2
blinker_v2_FFRE2
02
12T
PC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_FFRE.vhd2
418@Z8-256h px� 
�
Hmodule '%s' declared at '%s:%s' bound to instance '%s' of component '%s'3392*oasys2
blinker_v2_FFRE2R
PC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_FFRE.vhd2
342
ff12
blinker_v2_FFRE2X
TC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_pulsegen.vhd2
548@Z8-3491h px� 
�
%done synthesizing module '%s' (%s#%s)256*oasys2
blinker_v2_pulsegen2
02
12X
TC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_pulsegen.vhd2
408@Z8-256h px� 
�
Hmodule '%s' declared at '%s:%s' bound to instance '%s' of component '%s'3392*oasys2
blinker_v2_fsm2Q
OC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_fsm.vhd2
342	
dut_fsm2
blinker_v2_fsm2O
KC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2.vhd2
418@Z8-3491h px� 
�
synthesizing module '%s'638*oasys2
blinker_v2_fsm2S
OC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_fsm.vhd2
418@Z8-638h px� 
�
%done synthesizing module '%s' (%s#%s)256*oasys2
blinker_v2_fsm2
02
12S
OC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_fsm.vhd2
418@Z8-256h px� 
�
%done synthesizing module '%s' (%s#%s)256*oasys2

blinker_v22
02
12O
KC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2.vhd2
218@Z8-256h px� 
�
+Unused sequential element %s was removed. 
4326*oasys2
Q_reg2T
PC:/Dev/uni/master/II/Lab2/Lab1.srcs/sources_1/imports/design/blinker_v2_FFRE.vhd2
498@Z8-6014h px� 
�
%s*synth2{
yFinished RTL Elaboration : Time (s): cpu = 00:00:06 ; elapsed = 00:00:07 . Memory (MB): peak = 1033.148 ; gain = 568.715
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
;
%s
*synth2#
!Start Handling Custom Attributes
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Handling Custom Attributes : Time (s): cpu = 00:00:06 ; elapsed = 00:00:07 . Memory (MB): peak = 1033.148 ; gain = 568.715
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished RTL Optimization Phase 1 : Time (s): cpu = 00:00:06 ; elapsed = 00:00:07 . Memory (MB): peak = 1033.148 ; gain = 568.715
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
Netlist sorting complete. 2

00:00:002
00:00:00.0012

1033.1482
0.000Z17-268h px� 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px� 
>

Processing XDC Constraints
244*projectZ1-262h px� 
=
Initializing timing engine
348*projectZ1-569h px� 
�
Parsing XDC File [%s]
179*designutils2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc8Z20-179h px� 
�
No ports matched '%s'.
584*	planAhead2
led[0]2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
228@Z12-584h px�
�
"'%s' expects at least one object.
55*common2
set_property2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
228@Z17-55h px�
�
No ports matched '%s'.
584*	planAhead2
led[1]2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
238@Z12-584h px�
�
"'%s' expects at least one object.
55*common2
set_property2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
238@Z17-55h px�
�
No ports matched '%s'.
584*	planAhead2
led[2]2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
248@Z12-584h px�
�
"'%s' expects at least one object.
55*common2
set_property2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
248@Z17-55h px�
�
No ports matched '%s'.
584*	planAhead2
led[3]2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
258@Z12-584h px�
�
"'%s' expects at least one object.
55*common2
set_property2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
258@Z17-55h px�
�
Finished Parsing XDC File [%s]
178*designutils2b
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc8Z20-178h px� 
�
�Implementation specific constraints were found while reading constraint file [%s]. These constraints will be ignored for synthesis but will be used in implementation. Impacted constraints are listed in the file [%s].
233*project2`
^C:/Dev/uni/master/II/Lab2/Lab1.srcs/constrs_1/imports/SpartanConstraints/Cmod-S7-25-Master.xdc2
.Xil/blinker_v2_propImpl.xdcZ1-236h px� 
H
&Completed Processing XDC Constraints

245*projectZ1-263h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
Netlist sorting complete. 2

00:00:002

00:00:002

1094.5662
0.000Z17-268h px� 
l
!Unisim Transformation Summary:
%s111*project2'
%No Unisim elements were transformed.
Z1-111h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2"
 Constraint Validation Runtime : 2

00:00:002
00:00:00.0022

1094.5662
0.000Z17-268h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
Finished Constraint Validation : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
D
%s
*synth2,
*Start Loading Part and Timing Information
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
8
%s
*synth2 
Loading part: xc7s25csga225-1
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Loading Part and Timing Information : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
H
%s
*synth20
.Start Applying 'set_property' XDC Constraints
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished applying 'set_property' XDC Constraints : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
7
%s
*synth2
Start Preparing Guide Design
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
�The reference checkpoint %s is not suitable for use with incremental synthesis for this design. Please regenerate the checkpoint for this design with -incremental_synth switch in the same Vivado session that synth_design has been run. Synthesis will continue with the default flow4740*oasys2U
SC:/Dev/uni/master/II/Lab2/Lab1.srcs/utils_1/imports/synth_1/blinker_v2_pulsegen.dcpZ8-6895h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2~
|Finished Doing Graph Differ : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Preparing Guide Design : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
r
3inferred FSM for state register '%s' in module '%s'802*oasys2
	State_reg2
blinker_v2_fsmZ8-802h px� 
~
%s
*synth2f
d---------------------------------------------------------------------------------------------------
h p
x
� 
z
%s
*synth2b
`                   State |                     New Encoding |                Previous Encoding 
h p
x
� 
~
%s
*synth2f
d---------------------------------------------------------------------------------------------------
h p
x
� 
y
%s
*synth2a
_                state_s0 |                               00 |                               00
h p
x
� 
y
%s
*synth2a
_                state_s2 |                               01 |                               10
h p
x
� 
y
%s
*synth2a
_                state_s1 |                               10 |                               01
h p
x
� 
y
%s
*synth2a
_                state_s3 |                               11 |                               11
h p
x
� 
~
%s
*synth2f
d---------------------------------------------------------------------------------------------------
h p
x
� 
�
Gencoded FSM with state register '%s' using encoding '%s' in module '%s'3353*oasys2
	State_reg2

sequential2
blinker_v2_fsmZ8-3354h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished RTL Optimization Phase 2 : Time (s): cpu = 00:00:12 ; elapsed = 00:00:14 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
C
%s
*synth2+
)

Incremental Synthesis Report Summary:

h p
x
� 
<
%s
*synth2$
"1. Incremental synthesis run: no

h p
x
� 
O
%s
*synth27
5   Reason for not running incremental synthesis : 


h p
x
� 
�
�Flow is switching to default flow due to incremental criteria not met. If you would like to alter this behaviour and have the flow terminate instead, please set the following parameter config_implementation {autoIncr.Synth.RejectBehavior Terminate}4868*oasysZ8-7130h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
:
%s
*synth2"
 Start RTL Component Statistics 
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
9
%s
*synth2!
Detailed RTL Component Info : 
h p
x
� 
+
%s
*synth2
+---Registers : 
h p
x
� 
H
%s
*synth20
.	                1 Bit    Registers := 2     
h p
x
� 
'
%s
*synth2
+---Muxes : 
h p
x
� 
F
%s
*synth2.
,	   4 Input    2 Bit        Muxes := 1     
h p
x
� 
F
%s
*synth2.
,	   2 Input    2 Bit        Muxes := 4     
h p
x
� 
F
%s
*synth2.
,	   2 Input    1 Bit        Muxes := 1     
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
=
%s
*synth2%
#Finished RTL Component Statistics 
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
6
%s
*synth2
Start Part Resource Summary
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
o
%s
*synth2W
UPart Resources:
DSPs: 80 (col length:40)
BRAMs: 90 (col length: RAMB18 40 RAMB36 20)
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
9
%s
*synth2!
Finished Part Resource Summary
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
E
%s
*synth2-
+Start Cross Boundary and Area Optimization
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
H
&Parallel synthesis criteria is not met4829*oasysZ8-7080h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Cross Boundary and Area Optimization : Time (s): cpu = 00:00:13 ; elapsed = 00:00:16 . Memory (MB): peak = 1094.566 ; gain = 630.133
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
@
%s
*synth2(
&Start Applying XDC Timing Constraints
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Applying XDC Timing Constraints : Time (s): cpu = 00:00:18 ; elapsed = 00:00:21 . Memory (MB): peak = 1225.629 ; gain = 761.195
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
4
%s
*synth2
Start Timing Optimization
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2
}Finished Timing Optimization : Time (s): cpu = 00:00:18 ; elapsed = 00:00:21 . Memory (MB): peak = 1235.203 ; gain = 770.770
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
3
%s
*synth2
Start Technology Mapping
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2~
|Finished Technology Mapping : Time (s): cpu = 00:00:18 ; elapsed = 00:00:21 . Memory (MB): peak = 1235.711 ; gain = 771.277
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
-
%s
*synth2
Start IO Insertion
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
?
%s
*synth2'
%Start Flattening Before IO Insertion
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
B
%s
*synth2*
(Finished Flattening Before IO Insertion
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
6
%s
*synth2
Start Final Netlist Cleanup
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
9
%s
*synth2!
Finished Final Netlist Cleanup
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2x
vFinished IO Insertion : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
=
%s
*synth2%
#Start Renaming Generated Instances
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Renaming Generated Instances : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
:
%s
*synth2"
 Start Rebuilding User Hierarchy
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Rebuilding User Hierarchy : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
9
%s
*synth2!
Start Renaming Generated Ports
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Renaming Generated Ports : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
;
%s
*synth2#
!Start Handling Custom Attributes
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Handling Custom Attributes : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
8
%s
*synth2 
Start Renaming Generated Nets
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Renaming Generated Nets : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
9
%s
*synth2!
Start Writing Synthesis Report
h p
x
� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
/
%s
*synth2

Report BlackBoxes: 
h p
x
� 
8
%s
*synth2 
+-+--------------+----------+
h p
x
� 
8
%s
*synth2 
| |BlackBox name |Instances |
h p
x
� 
8
%s
*synth2 
+-+--------------+----------+
h p
x
� 
8
%s
*synth2 
+-+--------------+----------+
h p
x
� 
/
%s*synth2

Report Cell Usage: 
h px� 
0
%s*synth2
+------+-----+------+
h px� 
0
%s*synth2
|      |Cell |Count |
h px� 
0
%s*synth2
+------+-----+------+
h px� 
0
%s*synth2
|1     |BUFG |     1|
h px� 
0
%s*synth2
|2     |LUT2 |     1|
h px� 
0
%s*synth2
|3     |LUT3 |     1|
h px� 
0
%s*synth2
|4     |LUT4 |     1|
h px� 
0
%s*synth2
|5     |FDCE |     1|
h px� 
0
%s*synth2
|6     |FDPE |     1|
h px� 
0
%s*synth2
|7     |FDRE |     2|
h px� 
0
%s*synth2
|8     |IBUF |     3|
h px� 
0
%s*synth2
|9     |OBUF |     3|
h px� 
0
%s*synth2
+------+-----+------+
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
�
%s*synth2�
�Finished Writing Synthesis Report : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h px� 
l
%s
*synth2T
R---------------------------------------------------------------------------------
h p
x
� 
`
%s
*synth2H
FSynthesis finished with 0 errors, 1 critical warnings and 1 warnings.
h p
x
� 
�
%s
*synth2�
Synthesis Optimization Runtime : Time (s): cpu = 00:00:14 ; elapsed = 00:00:23 . Memory (MB): peak = 1452.441 ; gain = 926.590
h p
x
� 
�
%s
*synth2�
�Synthesis Optimization Complete : Time (s): cpu = 00:00:21 ; elapsed = 00:00:24 . Memory (MB): peak = 1452.441 ; gain = 988.008
h p
x
� 
B
 Translating synthesized netlist
350*projectZ1-571h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
Netlist sorting complete. 2

00:00:002

00:00:002

1452.4412
0.000Z17-268h px� 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px� 
Q
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02
0Z31-138h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
Netlist sorting complete. 2

00:00:002

00:00:002

1452.4412
0.000Z17-268h px� 
l
!Unisim Transformation Summary:
%s111*project2'
%No Unisim elements were transformed.
Z1-111h px� 
V
%Synth Design complete | Checksum: %s
562*	vivadotcl2

30feda32Z4-1430h px� 
C
Releasing license: %s
83*common2
	SynthesisZ17-83h px� 
~
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
302
62
52
0Z4-41h px� 
L
%s completed successfully
29*	vivadotcl2
synth_designZ4-42h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
synth_design: 2

00:00:242

00:00:472

1452.4412

1151.008Z17-268h px� 
c
%s6*runtcl2G
ESynthesis results are not added to the cache due to CRITICAL_WARNING
h px� 
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2
Write ShapeDB Complete: 2

00:00:002

00:00:002

1452.4412
0.000Z17-268h px� 
�
 The %s '%s' has been generated.
621*common2

checkpoint2<
:C:/Dev/uni/master/II/Lab2/Lab1.runs/synth_1/blinker_v2.dcpZ17-1381h px� 
�
Executing command : %s
56330*	planAhead2_
]report_utilization -file blinker_v2_utilization_synth.rpt -pb blinker_v2_utilization_synth.pbZ12-24828h px� 
\
Exiting %s at %s...
206*common2
Vivado2
Mon May 26 13:03:35 2025Z17-206h px� 


End Record