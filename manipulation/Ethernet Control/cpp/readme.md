
## Description

To connect to the UR robot and retrieve data by the socket.

All the data formatted by RealTime-Pre 3.0 right now because the robot I operated is an old one.

## Details

- platform: Windows 10
- dependencies: None
- compiler: MSVC 2017 x64

## Bugs
it cannot read in real-time. Specifically, the data from the UR robots is always the same one that first got.

## Example (data at first time)

``` 
received 4 bytes data successfully.
>>
data size=812
received 808 bytes data successfully.
>>@梹 臎ャ?鸷Z鷒PA?')髍??漌傀訟餑玒?鄡/梺?繍n坻
1504.03
1.0455 -3.01912 1.7993 -1.92682 0.516014 -0.0157411
0 0 0 0 0 0
0 0 0 0 0 0
2.53846e-17 2.51047 -0.420212 0.0179899 -0.000153302 0
3.24469e-16 32.2933 -5.39032 0.178921 -0.00152608 0
1.0455 -3.0191 1.79928 -1.92684 0.516016 -0.0157542
0 0 0 0 0 0
-0.141234 2.34493 -1.05589 0.0838773 0.218081 -0.247057
9.97947 0.497475 0.860093
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
-26.8163 -4.86466 -16.7654 2.40645 7.18445 -1.81036
0.32087 0.193182 0.603869 -1.22156 1.20834 -1.22965
0 0 0 0 0 0
0
30.1 29 28.5 31.2 34.3 35.2
0.025572
8
0
253 253 253 253 253 253
```