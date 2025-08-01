# Rampup Project

## Overview

Hello and welcome to the Electric Vehicle Team (EVT)! This project is designed 
to give you a look into what it is like to develop on the firmware team with. 
The goal is for you to get exposure to the full development life cycle at EVT, 
from prototyping with a breakout board to communicating between boards. This 
process is broken down into eight phases, each introducing a key part of our 
core library that the team uses all of our boards. Throughout the process you 
will learn everything you need to be a firmware engineer, from C++ fundamentals 
to class-level software design to hardware debugging.

If this is your first time doing embedded development, it will take some time 
to get used to all the new concepts and the quirks of working with hardware. 
Through this process, be sure to use all the resources at your disposal. Google 
is great for general C++ questions, and the firmware docs are useful for 
background on the tools we use for development, but when you're stuck, your 
best resource is going to be other firmware members, new and old. Collaboration 
is critical to our team's success, and it's often a lot more fun than grinding 
out code on your own!

## Getting started

Before getting started on the eight rampup phase, you need to first setup your
build environment in order to actually compile code. Start out by heading to the
[Environment Setup](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/getting-started/environment-setup)
page on the EVT website to install all the necessary tools for developing and 
compiling code. While you are waiting on all those tools to install, now is a 
perfect time to read up on [Git and Github](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/getting-started/version-control-git-and-github).

We primarily use Git and by extension Github ALOT. So it is important that you 
know a few basics. If you haven't used Git before, it might seem a bit 
overwhelming with all the different commands and terminology, but there is 
really only five key commands you need to know for 90% of your interactions 
with it. If any problems arise, Google is your friend when it comes to Git and 
is probably the best way to learn it. Your key commands are: 
 - `git clone [url]`  - This makes a local copy of a repository for you start
                        modifying code. 
 - `git pull` - This updates your local repository with changes on the server.
 - `git submodule update --init --recursive` - This downloads additional
                        repositories that are referenced in a project.
 - `git commit` - This allows you to submit your changes to the local
                  repository's history. 
 - `git push` - This pushes your local history to the remote server for other
                to view and edit.

With your environment setup and a crash course in Git, lets try it out! Start 
by cloning [EVT-core](https://github.com/RIT-EVT/EVT-core) to your local 
project folder with `git clone git@github.com:RIT-EVT/EVT-core.git` (If you do 
not have a project folder, we HIGHLY recommend you create one to store all of 
the different EVT repositories in to which you will clone many). Once you have 
EVT-core cloned, enter into the new directory and download all the submodules 
with `git submodule update --init --recursive` in order to get all the 
additional libraries we use. Finally follow the instruction in 
[Running Code](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/getting-started/running-code) 
to build the repository. If all goes well, you now have a fully functional 
build environment.

Now lets get you started on the rampup project! First, clone rampup to your 
project directory (NOT the EVT-core directory!) with 
`git clone git@github.com:RIT-EVT/rampup.git`. Again, update your submodules 
with `git submodule update --init --recursive` to get the included copy of 
EVT-core and libraries. With the repository cloned, its time to get started 
with Phase 0.

## Phase 0: C++

Phase 0 is a short introduction C++ if you have never used it before. If you are comfortable with C++ object orientated programming, go a head an skip to Phase 1. 

To get started, follow the instructions in [targets/phase0](targets/phase0/Instructions.md).

## Phase 1: GPIO

To get started, follow the instructions in [targets/phase1](targets/phase1/Instructions.md).

## Phase 2: UART

To get started, follow the instructions in [targets/phase2](targets/phase2/Instructions.md).

## Phase 3: I2C

To get started, follow the instructions in [targets/phase3](targets/phase3/Instructions.md).

## Phase 4: SPI

To get started, follow the instructions in [targets/phase4](targets/phase4/Instructions.md).

## Phase 5: ADC

To get started, follow the instructions in [targets/phase5](targets/phase5/Instructions.md).

## Phase 6: CAN

To get started, follow the instructions in [targets/phase6](targets/phase6/Instructions.md).

## Phase 7: CANOpen

To get started, follow the instructions in [targets/phase7](targets/phase7/Instructions.md).

## Next Steps

Congratulations on completing the rampup project! If you're new to firmware
development, starting something new like this can be very time-consuming and
difficult, but you met that challenge and overcame it. I hope you got a good
idea of how the firmware team operates and the type of work we do as a team.
Having completed the rampup project, you are now a fully-fledged member of our
team, so you can begin work on a project for one of our bikes. If there's
anything else you want to learn about or don't understand, be sure to take some
time now to read over some documentation and play around with it now. Once you
think you're ready, you can reach out to the firmware lead to get your first
project.

Good luck!
