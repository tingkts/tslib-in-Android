# Code design
The overall architecture is composed of three modules (or called three processes), which work together in tandem (they serial execution) to complete the touch screen correction function.


## Modules and its process

### TsCalibrator

Play the role of an entry of the activity to display UI for the end-user to select the target touch screen device, and then click the button to confirm to perform touch screen calibration.

```
LABEL                          USER           PID  PPID     VSZ    RSS WCHAN            ADDR S NAME
u:r:system_app:s0              system        3268  2390 4035444 181772 SyS_epoll_wait 7981f70668 S com.tslib.calibrator
```
|  data I/O | persistence file |
| ---- | ---- |
| _read_ | N/A |
| _write_ | /data/system/tscalibrate/active_tsdevice |




### ts_calibrate

Play the role of a caculator to output the calibration parameters of the affine trasformation, it's the known open source of [libts/tslib](https://github.com/libts/tslib) as the touchscreen access library and have serveral touch event filter algorithms of touch screen devices.

```
LABEL                          USER           PID  PPID     VSZ    RSS WCHAN            ADDR S NAME
u:r:tscalibrate:s0             root          3318     1   42464  35484 evdev_read 7335f70190 S ts_calibrate
```

|  data I/O | persistence file |
| ---- | ---- |
| _read_ | /data/system/tscalibrate/active_tsdevice |
| _write_ | /data/system/tscalibrate/*descriptor*_*rotation* |



### InputManagerService

Play the role to apply the the touch screen calibration affine transformation, and persist the data of the calibration parameters.

```
LABEL                          USER           PID  PPID     VSZ    RSS WCHAN            ADDR S NAME
u:r:system_server:s0           system        3331  3324 4903020 269728 SyS_epoll_wait 7283a33668 S system_server
```

|  data I/O | persistence file |
| ---- | ---- |
| _read_ | /data/system/tscalibrate/active_tsdevice <br /> /data/system/tscalibrate/*descriptor*_*rotation*|
| _write_ | /data/system/input-manager-state.xml |


<br />


> The more data stream I/O details are written in [metadata/README.md](./metadata/README.md).

<br />


## Issues

### Surface rotation

Returns the rotation of the screen from its "natural" orientation. The returned value may be Surface#ROTATION_0 (no rotation), Surface#ROTATION_90, Surface#ROTATION_180, or Surface#ROTATION_270. For example, if a device has a naturally tall screen, and the user has turned it on its side to go into a landscape orientation, the value returned here may be either Surface#ROTATION_90 or Surface#ROTATION_270 depending on the direction it was turned. The angle is the rotation of the drawn graphics on the screen, which is the opposite direction of the physical rotation of the device. For example, if the device is rotated 90 degrees counter-clockwise, to compensate rendering will be rotated by 90 degrees clockwise and thus the returned value here will be Surface#ROTATION_90.

|  name | value |
| ---- | ---- |
| [Surface.ROTATION_0](https://developer.android.com/reference/android/view/Surface.html#ROTATION_0) | 0 |
| [Surface.ROTATION_90](https://developer.android.com/reference/android/view/Surface.html#ROTATION_90) | 1 |
| [Surface.ROTATION_180](https://developer.android.com/reference/android/view/Surface.html#ROTATION_180) | 2 |
| [Surface.ROTATION_270](https://developer.android.com/reference/android/view/Surface.html#ROTATION_270) | 3 |


<br />


## Notes

* lib/ts/plugins/*.so dlopen() fail issue.
* init.rc can't make symlink in /system, access /system needs remount first.
* ```
  // sepolicy context
  console:/ # ls -Z    // file
  console:/ # ps -Z    // process
  console:/ # id -Z    // current user
  ```
