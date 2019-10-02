# AQM

## Get Project
```sh
git clone https://github.com/nemusou/AQM
# or Download ZIP from github
cd AQM
```

## Compile and Run
```sh
cd src
gcc example.c acf.c readfile.c findpeaks.c -o example
./example

# or

cd src
make
./example
```

### 入力例 [input/input.csv](https://github.com/nemusou/AQM/blob/develop/input/input.csv)
```sh
cd input
less input.csv
```

### 実行結果 [output/output.csv](https://github.com/nemusou/AQM/blob/develop/output/output.csv) [output/output2.csv](https://github.com/nemusou/AQM/blob/develop/output/output2.csv)
```sh
cd output
less output.csv
```

## Develop Environment
Apple LLVM version 10.0.1 (clang-1001.0.46.4)  
Target: x86\_64-apple-darwin18.6.0  
Thread model: posix  
