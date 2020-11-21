(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: drill_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Saturday, 21 November 2020 at 18:07)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 0.76)
(Tool: 2 -> Dia: 0.762)
(Tool: 3 -> Dia: 0.8)
(Tool: 4 -> Dia: 1.0)
(Tool: 5 -> Dia: 1.016)
(Tool: 6 -> Dia: 1.2)
(Tool: 7 -> Dia: 1.52)
(Tool: 8 -> Dia: 0.9)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 60.0)
(Tool: 2 -> Feedrate: 60.0)
(Tool: 3 -> Feedrate: 60.0)
(Tool: 4 -> Feedrate: 60.0)
(Tool: 5 -> Feedrate: 60.0)
(Tool: 6 -> Feedrate: 60.0)
(Tool: 7 -> Feedrate: 60.0)
(Tool: 8 -> Feedrate: 60.0)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 150.0)
(Tool: 2 -> Feedrate Rapids: 150.0)
(Tool: 3 -> Feedrate Rapids: 150.0)
(Tool: 4 -> Feedrate Rapids: 150.0)
(Tool: 5 -> Feedrate Rapids: 150.0)
(Tool: 6 -> Feedrate Rapids: 150.0)
(Tool: 7 -> Feedrate Rapids: 150.0)
(Tool: 8 -> Feedrate Rapids: 150.0)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -1.8)
(Tool: 2 -> Z_Cut: -1.8)
(Tool: 3 -> Z_Cut: -1.8)
(Tool: 4 -> Z_Cut: -1.8)
(Tool: 5 -> Z_Cut: -1.8)
(Tool: 6 -> Z_Cut: -1.8)
(Tool: 7 -> Z_Cut: -1.8)
(Tool: 8 -> Z_Cut: -1.8)

(Tools Offset: )
(Tool: 4 -> Offset Z: 0.0)
(Tool: 6 -> Offset Z: 0.0)
(Tool: 7 -> Offset Z: 0.0)
(Tool: 8 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 2)
(Tool: 2 -> Z_Move: 2)
(Tool: 3 -> Z_Move: 2)
(Tool: 4 -> Z_Move: 2)
(Tool: 5 -> Z_Move: 2)
(Tool: 6 -> Z_Move: 2)
(Tool: 7 -> Z_Move: 2)
(Tool: 8 -> Z_Move: 2)

(Z Toolchange: 20.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 20.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)

(X range:    3.9900 ...  139.0100  mm)
(Y range:    3.5880 ...   91.9710  mm)

(Spindle Speed: 12000 RPM)
G21
G90
G94

G01 F60.00

M5
G00 Z20.0000
T4
G00 X0.0000 Y0.0000                
M6
(MSG, Change to Tool Dia = 1.0000 ||| Total drills for tool T4 = 54)
M0
G00 Z20.0000

G01 F60.00
M03 S12000
G00 X67.9700 Y34.6700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X67.9700 Y32.1300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X78.2600 Y21.9700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X78.2600 Y14.3500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X67.9700 Y14.3500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X67.9700 Y21.9700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X57.9400 Y32.1300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X57.9400 Y34.6700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X57.9400 Y21.9700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X57.9400 Y14.3500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X45.1100 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X40.0300 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X34.9500 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X29.8700 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X13.3600 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X8.2800 Y15.6200
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X8.2800 Y27.0500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X28.6000 Y27.0500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X31.6000 Y49.7300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X31.6000 Y70.0500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X20.9800 Y76.5800
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X15.0900 Y80.2100
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X11.5900 Y80.2100
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X8.0900 Y80.2100
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X4.5900 Y80.2100
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X20.9800 Y81.6600
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X33.6800 Y81.6600
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X33.6800 Y76.5800
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X60.3500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X63.8500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X67.3500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X70.8500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X74.3500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X77.8500 Y80.3900
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X90.8900 Y83.9300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X95.9700 Y83.9300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X90.9790 Y91.2110
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X96.0590 Y91.2110
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.1390 Y91.2110
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X106.2190 Y91.2110
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.0500 Y83.9300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X106.1300 Y83.9300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X138.4100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X134.9100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X131.4100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X127.9100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X124.4100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X120.9100 Y30.7700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.0500 Y11.5500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.0500 Y14.0500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.0500 Y16.5500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X101.0500 Y19.0500
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X78.2600 Y32.1300
G01 Z-1.8000
G01 Z0
G00 Z2.0000
G00 X78.2600 Y34.6700
G01 Z-1.8000
G01 Z0
G00 Z2.0000
M05
G00 Z20.00

