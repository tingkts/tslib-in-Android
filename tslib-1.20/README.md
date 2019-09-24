
# About tslib in Android
This page is the memo record of how to porting the well-known library [libts/tslib](https://github.com/libts/tslib) into android 9. And, use it's binary tool [ts_calibrate](./tslib-1.20/tests/ts_calibrate) to perform touch screen calibration and [ts_test_mt](./tslib-1.20/tests/ts_test_mt) to verify the effect after applying calibrated parameters.
<p align="right">| Based on AOSP Android 9.0.0 of Rockchip RK3399 SOC platform</p>


## build tslib with aosp
1. download open source [tslib 1.20](./tslib-1.20) and put it into /external/tslib

2.  auto generate [config.h](./aosp_patches/external/tslib/config.h) in tslib folder
    ```
    console:/ $ cd external/tslib/
    console:/ $ ./autogen.sh
    console:/ $ ./configure
    ```



3. apply [patch](./0001-porting-tslib-into-android.patch) to modify tslib [Android.mk](./tslib-1.20/Android.mk) to avoid build break and print debug log.
    ```
    console:/ $ cd external/tslib/
    console:/ $ git am 0001-porting-tslib-into-android.patch
    ```


4. module build tslib with android

      ```
      # cd aosp root directory and execute "set up environment" and "choose a target"

      console:/ $ cd aosp_root
      console:/ $ source build/envsetup.sh
      console:/ $ lunch *product_name*-eng     (e.g. lunch aosp_arm64-eng or aosp_arm64-user)
      console:/ $
      console:/ $ # cd tslib folder to execute android module build command, mma
      console:/ $ cd aosp_root/external/tslib
      console:/ $ mma -j8
      ```


5. check [output binary and library](./outputs) (build in system folder and package into system.img)
   ```
   # enter aosp product out (echo $ANDROID_PRODUCT_OUT)

      console:/ $ cd out/target/product/*product_name*/

   # check binary executable in system/bin/

      system/bin/ts_calibrate
      system/bin/ts_print
      system/bin/ts_print_mt
      system/bin/ts_print_raw
      system/bin/ts_test_mt
      system/bin/ts_uinput

   # check library in system/lib/ and system/lib64/

      system/lib/libts.so
      system/lib/ts/plugins/pthres.so
      system/lib/ts/plugins/input.so
      system/lib/ts/plugins/iir.so
      system/lib/ts/plugins/lowpass.so
      system/lib/ts/plugins/debounce.so
      system/lib/ts/plugins/invert.so
      system/lib/ts/plugins/skip.so
      system/lib/ts/plugins/median.so
      system/lib/ts/plugins/dejitter.so
      system/lib/ts/plugins/linear.so

      system/lib64/libts.so
      system/lib64/ts/plugins
      system/lib64/ts/plugins/pthres.so
      system/lib64/ts/plugins/input.so
      system/lib64/ts/plugins/iir.so
      system/lib64/ts/plugins/lowpass.so
      system/lib64/ts/plugins/debounce.so
      system/lib64/ts/plugins/invert.so
      system/lib64/ts/plugins/skip.so
      system/lib64/ts/plugins/median.so
      system/lib64/ts/plugins/dejitter.so
      system/lib64/ts/plugins/linear.so
   ```


<br>

## Setup environment variables and config file in device console

* setup environment variables

  > tslib binary executable must be executed with the root permission, so use [su](/system/extras/su/) to switch to root user.

  ```
  console:/ $ adb sehll
  console:/ $ su
  console:/ # export TSLIB_TSDEVICE=/dev/input/event2               (depends on which your touch screen input device)
  console:/ # export TSLIB_PLUGINDIR=/system/lib64/ts/plugins
  console:/ # export TSLIB_CONSOLEDEVICE=none;
  console:/ # export TSLIB_CALIBFILE=/data/pointercal
  console:/ # export TSLIB_FBDEVICE=/dev/graphics/fb0
  ```

* setup config file, [ts.conf](./tslib-1.20/etc/ts.conf)

  ```
  console:/ $ adb remount
  console:/ $ adb push ts.conf /system/etc/ts.conf
  ```

<br>

## Run ts_calibrate

   execute ts_calibrate to perform touch screen calibration, and it'll output calibration parameters(10 integers).
  ```
  console:/ $ su
  console:/ # ts_calibrate
  ```

   debug log :

   ```
   console:/ # tslib 1.20+ / libts ABI version 0 (0x000A02)
   console:/ # Release-Date: [unreleased]
   console:/ #  Host OS: Linux, trying to open /dev/input/event2
   console:/ # Loading module input
   console:/ # Loading module pthres (pmin=1)
   console:/ # Loading module dejitter (delta=100)
   console:/ # Loading module linear
   console:/ # xres = 3840, yres = 2160
   console:/ # tslib input device: vendor 0x2575 product 0x5130 version 0x110 on bus 0x3
   console:/ # tslib: No pressure values. We fake it internally
   console:/ # RAW---------------------> 1767 1682 255 1568969879.955893
   console:/ # TS_READ_RAW----> x = 1767, y = 1682, pressure = 255
   console:/ # RAW---------------------> 1768 1673 255 1568969880.87658
   console:/ # TS_READ_RAW----> x = 1768, y = 1673, pressure = 255
   console:/ # RAW---------------------> 0 0 0 1568969880.135795
   console:/ # TS_READ_RAW----> x = 0, y = 0, pressure = 0
   console:/ # Took 2 samples...
   console:/ # Top left : X = 1767 Y = 1677
   console:/ # RAW---------------------> 31728 2720 255 1568969881.12904
   console:/ # TS_READ_RAW----> x = 31728, y = 2720, pressure = 255
   console:/ # RAW---------------------> 31728 2718 255 1568969881.30787
   console:/ # TS_READ_RAW----> x = 31728, y = 2718, pressure = 255
   console:/ # RAW---------------------> 31728 2715 255 1568969881.38730
   console:/ # TS_READ_RAW----> x = 31728, y = 2715, pressure = 255
   console:/ # RAW---------------------> 31728 2713 255 1568969881.54795
   console:/ # TS_READ_RAW----> x = 31728, y = 2713, pressure = 255
   console:/ # RAW---------------------> 0 0 0 1568969881.183783
   console:/ # TS_READ_RAW----> x = 0, y = 0, pressure = 0
   console:/ # Took 4 samples...
   console:/ # Top right : X = 31728 Y = 2716
   console:/ # RAW---------------------> 0 32767 255 1568969882.28901
   console:/ # TS_READ_RAW----> x = 0, y = 32767, pressure = 255
   console:/ # RAW---------------------> 10 32725 255 1568969882.31765
   console:/ # TS_READ_RAW----> x = 10, y = 32725, pressure = 255
   console:/ # RAW---------------------> 21 32686 255 1568969882.38673
   console:/ # TS_READ_RAW----> x = 21, y = 32686, pressure = 255
   console:/ # RAW---------------------> 39 32640 255 1568969882.46664
   console:/ # TS_READ_RAW----> x = 39, y = 32640, pressure = 255
   console:/ # RAW---------------------> 55 32594 255 1568969882.54794
   console:/ # TS_READ_RAW----> x = 55, y = 32594, pressure = 255
   console:/ # RAW---------------------> 71 32551 255 1568969882.62797
   console:/ # TS_READ_RAW----> x = 71, y = 32551, pressure = 255
   console:/ # RAW---------------------> 78 32521 255 1568969882.70783
   console:/ # TS_READ_RAW----> x = 78, y = 32521, pressure = 255
   console:/ # RAW---------------------> 86 32496 255 1568969882.79786
   console:/ # TS_READ_RAW----> x = 86, y = 32496, pressure = 255
   console:/ # RAW---------------------> 92 32473 255 1568969882.87667
   console:/ # TS_READ_RAW----> x = 92, y = 32473, pressure = 255
   console:/ # RAW---------------------> 104 32443 255 1568969882.95787
   console:/ # TS_READ_RAW----> x = 104, y = 32443, pressure = 255
   console:/ # RAW---------------------> 110 32423 255 1568969882.103777
   console:/ # TS_READ_RAW----> x = 110, y = 32423, pressure = 255
   console:/ # RAW---------------------> 122 32395 255 1568969882.111786
   console:/ # TS_READ_RAW----> x = 122, y = 32395, pressure = 255
   console:/ # RAW---------------------> 133 32373 255 1568969882.119787
   console:/ # TS_READ_RAW----> x = 133, y = 32373, pressure = 255
   console:/ # RAW---------------------> 138 32361 255 1568969882.127776
   console:/ # TS_READ_RAW----> x = 138, y = 32361, pressure = 255
   console:/ # RAW---------------------> 138 32359 255 1568969882.135611
   console:/ # TS_READ_RAW----> x = 138, y = 32359, pressure = 255
   console:/ # RAW---------------------> 145 32359 255 1568969882.144611
   console:/ # TS_READ_RAW----> x = 145, y = 32359, pressure = 255
   console:/ # RAW---------------------> 147 32357 255 1568969882.152610
   console:/ # TS_READ_RAW----> x = 147, y = 32357, pressure = 255
   console:/ # RAW---------------------> 0 0 0 1568969882.199793
   console:/ # TS_READ_RAW----> x = 0, y = 0, pressure = 0
   console:/ # Took 17 samples...
   console:/ # Bot right : X =   92 Y = 32473
   console:/ # RAW---------------------> 30960 31442 255 1568969882.996890
   console:/ # TS_READ_RAW----> x = 30960, y = 31442, pressure = 255
   console:/ # RAW---------------------> 30960 31445 255 1568969883.102711
   console:/ # TS_READ_RAW----> x = 30960, y = 31445, pressure = 255
   console:/ # RAW---------------------> 0 0 0 1568969883.174794
   console:/ # TS_READ_RAW----> x = 0, y = 0, pressure = 0
   console:/ # Took 2 samples...
   console:/ # Bot left : X = 30960 Y = 31443
   console:/ # RAW---------------------> 14861 16720 255 1568969883.841796
   console:/ # TS_READ_RAW----> x = 14861, y = 16720, pressure = 255
   console:/ # RAW---------------------> 14861 16722 255 1568969883.930786
   console:/ # TS_READ_RAW----> x = 14861, y = 16722, pressure = 255
   console:/ # RAW---------------------> 14864 16727 255 1568969883.938793
   console:/ # TS_READ_RAW----> x = 14864, y = 16727, pressure = 255
   console:/ # RAW---------------------> 0 0 0 1568969883.986784
   console:/ # TS_READ_RAW----> x = 0, y = 0, pressure = 0
   console:/ # Took 3 samples...
   console:/ # Center : X = 14861 Y = 16722
   console:/ # 1873.324707 -0.001660 0.004294
   console:/ # -95.465576 -0.000006 0.069125
   console:/ # Calibration constants: 122770208 -108 281 -6256432 0 4530 65536
   ```

<br>

## Run ts_test_mt

  execute ts_test_mt to verify the accuracy of ts_calibrate output parameters.

  ```
  console:/ $ su
  console:/ # ts_test_mt
  ```
<br>


## Calibration formula

  [TouchAffineTransformation](http://androidxref.com/9.0.0_r3/xref/frameworks/native/services/inputflinger/InputReader.cpp#322)
  ```
  321// -- TouchAffineTransformation --
  322void TouchAffineTransformation::applyTo(float& x, float& y) const {
  323    float newX, newY;
  324    newX = x * x_scale + y * x_ymix + x_offset;
  325    newY = x * y_xmix + y * y_scale + y_offset;
  326
  327    x = newX;
  328    y = newY;
  329}
  330
  ```

<br />

## References

* Official website : [tslib.org](http://www.tslib.org/), [GitHub libts/tslib](https://github.com/libts/tslib)

* [小耕的隨手筆記: TSLIB on Android gingerbread](http://notebyedward.blogspot.com/2013/12/tslib-on-android-gingerbread.html)

* [Android6.0移植tslib去实现电阻屏校准 - qq_42233843的博客 - CSDN博客](https://blog.csdn.net/qq_42233843/article/details/89420262)

* [is not accessible for the namespace default - Google 搜尋](https://www.google.com/search?q=is+not+accessible+for+the+namespace+default&oq=is+not+accessible+for+the+namespace+default&aqs=chrome..69i57j0l2j69i64j69i65.3558j0j0&sourceid=chrome&ie=UTF-8)



