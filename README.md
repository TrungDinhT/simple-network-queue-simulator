# How to build

Clone the repository and change build script to executable mode:
```
$ chmod u+x build
```

Then, run build with the right option for each question. For example, there are: --q1 for question 1 about random C program, --q2 for question 2 about infinite queue simulator, --q5 for question 5 about finite queue simulator. There are also other options for debug and other parameters. Run build with --help gives following result:
```
$ ./build --help
usage: ./build [options]
options:
  --q1: build random program for question 1
  --q2: build simulator for question 2 (infinite buffer)
  --q5: build simulator for question 5 (finite buffer)
  --enable-debug: print results to screen
  --disable-debug: save result to csv file in output/
  --enable-multithreading allows to run simulation in multithread (used for finite queue with different queue sizes)
  --disable-multithreading does not allow to run simulation in multithread
  --inf_queue: infinite buffer for simulator
  --fin_queue: finite buffer for simulator
default option is --enable-debug, --disable-multithreading and --inf_queue
```
