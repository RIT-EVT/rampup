# Getting Started

This guide gets your computer ready to build, flash, and talk to code on EVT
hardware. Do this **before** starting [Phase 1](../README.md#phase-1-uart).
None of the rampup phases will make sense if you can't build and flash yet.

If you've never done embedded development before, expect this page to take
a while the first time, especially on Windows. That's normal. Ask a senior
firmware member if you get stuck on anything below; setup issues are almost
always something someone else has already hit.

## 1. Install the tools

You need four things: Git, CMake, the ARM GCC compiler, and an editor/IDE.

- **Git** - [git-scm.com](https://git-scm.com/downloads). You likely already
  have this if you cloned this repo.
- **CMake** - [cmake.org/download](https://cmake.org/download/). This is the
  build system that turns our C++ source into a program the board can run.
- **GCC ARM toolchain** - This is the actual compiler that turns C++ into
  code the microcontroller understands (your laptop's normal compiler can't
  do this; it targets your laptop's CPU, not the board's). Arm doesn't
  publish a formal "LTS" release track for this toolchain, so just grab
  whatever is newest: download it for your platform from the
  [arm-none-eabi-gcc releases page](https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases/latest)
  (as of writing, the latest is `v15.2.1-1.1`; pick the top-most release and
  the archive matching your OS). On Mac/Linux, this comes as a `.tar.gz`
  you extract; on Windows, a `.zip`.
  1. <u>**_Note where you extracted it_**</u>, then find the `bin/` folder inside it.
  2. Set an environment variable named `GCC_ARM_TOOLS_PATH` pointing at that
     `bin/` folder:
     - **Windows:** [create a user environment variable](https://phoenixnap.com/kb/windows-set-environment-variable)
       named `GCC_ARM_TOOLS_PATH`, value = the `bin` folder. Restart your
       terminal (or your machine) afterward.
     - **Mac/Linux:** add this line to `~/.zshrc` (Mac default) or
       `~/.bashrc` (Linux), then restart your terminal:
       ```bash
       export GCC_ARM_TOOLS_PATH=/path/to/gcc-arm-toolchain/bin/
       ```
  Our CMake setup reads this variable to find the compiler. If it's not
  set correctly, the build will fail immediately, so it's worth double
  checking this step if nothing else works.
- **An IDE:**
  - **CLion is recommended and what most of the team uses.** It handles
    the CMake configuration and flashing/debugging integration for you (see
    below). CLion has a free version, but students can get a full license for free
  from [JetBrains' student license](https://www.jetbrains.com/community/education/#students).
  - VS Code with the CMake Tools extension also works, as does building
    from the command line directly.

## 2. Get the code

This repo depends on **EVT-core**, our shared hardware abstraction library,
which is included as a git submodule. If you haven't cloned this repo yet:

```bash
git clone --recurse-submodules <this-repo-url>
```

If you already cloned it without that flag (or the `libs/EVT-core` folder looks empty):

```bash
git submodule update --init --recursive
```

## 3. Build the code

First, figure out which Nucleo board you have. Look for a label like
`NUCLEO-F334R8` or `NUCLEO-F302R8` printed on the board itself. The `F334` or
`F302` part is what matters; it tells CMake which chip to compile for via
the `TARGET_DEV` flag.

**In CLion:**
1. Open the repo's top-level folder as a CLion project.
2. Go to `File → Settings...` (`CLion → Preferences...` on Mac) →
   `Build, Execution, Deployment → CMake`.
3. In the **"CMake options"** field, enter:
   ```
   -DTARGET_DEV=STM32F302x8 -DEVT_CORE_LOG_ENABLE=1
   ```
   swapping in `STM32F334x8` if that's what's printed on your Nucleo. This
   is the setting that tells the compiler which chip you're targeting. The second part, with `..._LOG_ENABLE` 
is telling the compiler to have logging so we are able to debug our firmware during development. It's
   easy to skip, and skipping it won't always give you an obvious error when your code doesn't work.
   **If your board is an F302 and you skip this step, your code will build
   "successfully" but may not run correctly on your board**, so don't skip
   it even if the build seems to work without it.
4. In the **"Build Directory"** field, enter: 
```
build
```
This will tell the compiler to output any code produced into a folder named build.

5. In the **"Build Options"** field, enter:
```
-j 20
```
This field passes flags to the underlying build tool instead of to CMake itself. 
`-j 20` tells it to compile up to 20 files in parallel, which speeds up the build 
on multi-core machines. Feel free to raise or lower the number to match how many 
cores your machine has.

6. Click "OK" / "Apply." CLion will reload CMake in the background. Wait
   for that to finish (watch the status bar at the bottom) before building.

7. Use the target dropdown in the top-right to pick which target to build
   (e.g. `phase1`), then click the green hammer icon to build, or the green
   play/bug icon to build and run/debug.

If you ever need to change chip target later (e.g. you switch to a
different Nucleo), go back to this same settings page, edit the option, and
reload CMake; you don't need to re-create the project.

If the build fails immediately with something about a missing compiler,
re-check the `GCC_ARM_TOOLS_PATH` environment variable from step 1; that's
the most common cause.

Built files land in `build/targets/<phase>/`, including a `.bin` file, which
is what you'll flash onto the board.

## 4. Flash your code onto the board

**Flashing Nucleo boards via USB:**
- Plug the Nucleo in via USB. It shows up as a removable drive.
- Find where your generated code is (i.e. `build/targets/phase1/phase1.bin`)
- **Windows:** open the Nucleo external device in File Explorer and copy the `.bin` file onto it.
- **Mac/Linux:** it mounts like a USB stick (e.g. `/media/<you>/NODE_F334R8`
  on Linux); copy the file the same way, or through the command line e.g.
  `cp build/targets/phase1/phase1.bin /Volumes/NODE_F334R8/`.
- A green/red LED blinks while it's programming and stops when done.

**Flashing EVT custom boards, via ST-Link:**
- Install [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html).
- Connect the ST-Link to the board's JTAG header and to your computer.
- Open STM32CubeProgrammer, go to "Erasing and Programming," select the
  board under ST-LINK configuration, and click "Connect."
- Set the file path to your `.bin` file and click "Start Programming."

**CLion can do this step for you** on either type of board: create a Run
Configuration using the "OpenOCD Download & Run" template, point it at your
target executable and the appropriate `.cfg` file (e.g. `st_nucleo_f3.cfg`),
and hit the play button to build + flash in one step. Ask a senior member if
you want help setting this up; it saves a lot of manual copying later on.

## 5. Talk to your board (serial console)

Most rampup phases print output over UART, which you read using a serial
console on your laptop, at **9600 baud**.

- **Windows:** [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html). Find your COM port via
  Device Manager → "Ports (COM & LPT)" (e.g. `COM5`). In PuTTY, set
  Connection Type to "Serial," enter the COM port and baud rate 9600.
- **Mac/Linux:** use `screen` (built in) or download a friendlier option for macOS, [cereal](https://github.com/ActuallyTaylor/cereal):
  ```bash
  screen /dev/tty.usbmodem* 9600      # Mac, path will vary
  screen /dev/ttyACM0 9600            # Linux, path will vary
  ```
  To exit `screen`, press `Ctrl-A` then `K`, then confirm.

## 6. Sanity-check your setup

Before starting Phase 1, it's worth confirming the whole toolchain works
using something simpler than rampup code. Build and flash the `blink-test`
target from `targets/blink-test`.

Flash `build/targets/blink-test/blink-test.bin` the same way described in
step 4. If an LED on the board starts blinking, your compiler, CMake setup,
and flashing process all work; any issues you hit from here on out will be
about the rampup code itself, not your environment.

## Troubleshooting

- **Build fails immediately, mentions a missing compiler or `arm-none-eabi`:**
  `GCC_ARM_TOOLS_PATH` isn't set, or points to the wrong folder. It must
  point directly at the `bin/` folder containing `arm-none-eabi-gcc`.
- **CMake complains about `TARGET_DEV` / "not supported":** you either
  didn't pass `-DTARGET_DEV=...` or misspelled it. Valid values in this repo
  are `STM32F302x8` and `STM32F334x8`.
- **Board doesn't show up as a drive:** try a different USB cable (some are
  power-only) and a different port.
- **Serial console shows nothing:** double check the baud rate is 9600 and
  that you're pointed at the right port. Unplug/replug the board and see
  which port disappears/reappears in Device Manager (Windows) or `ls
  /dev/tty.*` (Mac) to identify it.
- **Still stuck:** bring a senior firmware member the exact error message.
  "It doesn't work" is much harder to debug than a copy-pasted error.

Once you're through this page, head back to the [README](../README.md) and
start Phase 1.
