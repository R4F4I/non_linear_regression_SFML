# non linear regression simulation




https://github.com/user-attachments/assets/9b22fab3-3081-41b1-918c-8c2385a50ce8



# about

- continuation of [regression model in C](https://github.com/R4F4I/non-Linear-Regression-in-C)
- will show a simulation of the hypothesis fitting the data
- place the `data.txt` and `parameters.txt` in the same directory as the `.exe`
- the process will continue estimating parameters until the windows is not closed
- after closing, the window, the bin will output the finalized parameters at the same path

the following data format is to be followed respectively, (you can use for a demo)

# test Data

*data.txt*
```
-3.00,9.00
-2.74,7.50
-2.47,6.10
-2.21,4.80
-1.95,3.60
-1.68,2.50
-1.42,1.50
-1.16,0.60
-0.89,-0.20
-0.63,-0.90
-0.37,-1.50
-0.10,-2.00
0.16,-2.40
0.42,-2.70
0.68,-2.90
0.95,-3.00
1.21,-3.00
1.47,-2.90
1.74,-2.70
2.00,-2.40
```

*parameters.txt*
```
0
0
-1
0.12
0
0
-0.02
0.723
-1.48
-10.04
```

> [!note]
> - if the initial parameters presented has a loss greater than 10 the program will instead randomly generate random numbers until it reaches a combination with an error less than 10
> - this might lead to program being stuck in an indefinite loop, which is why it is better to give the program the estimated parameters manually


# building from source

```
mkdir build
cd build
cmake ..
```

- open `build/non-linear-regression.sln` using `VS`
- set the folder of same name as `startup project`
- build

- move to `build/Debug`
- the bin is there
