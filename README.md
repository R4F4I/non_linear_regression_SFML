# non linear regression simulation
<video controls src="20250625-0941-03.0036260.mp4" title="Title"></video>

# about

- continuation of [regression model in C](https://github.com/R4F4I/non-Linear-Regression-in-C)
- will show a simulation of the hypothesis fitting the data
- place the `data.txt` and `parameters.txt` in the same directory as the `.exe`
- the process will continue estimating parameters until the windows is not closed
- after closing, the window, the bin will output the finalized parameters at the same path

the following data format is to be followed respectively,


*data.txt*
```
-3.14,0.00
-2.79,-0.35
-2.45,-0.64
-2.11,-0.86
-1.76,-0.98
-1.42,-0.99
-1.07,-0.88
-0.73,-0.67
-0.39,-0.38
-0.04,-0.04
0.30,0.30
0.64,0.60
0.99,0.84
1.33,0.97
1.68,0.99
2.02,0.90
2.36,0.71
2.71,0.41
3.05,0.10
3.14,0.00
```

*parameters.txt*
```
0
0
0.500129
0
0
0
-6
-838708
11.0008
4.50013
```

> [!note]
> - if the initial parameters presented has a loss greater than 10 the program will instead randomly generate random numbers until it reaches a combination with an error less than 10
> - this might lead to program being stuck in an indefinite loop, which is why it is better to give the program the estimated parameters manually