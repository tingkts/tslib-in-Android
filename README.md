# apply ts_calibrate in Android of touch screen calibration
Porting [tslib](https://github.com/libts/tslib) into android and wrap [ts_calibrate](https://github.com/libts/tslib/blob/master/tests/ts_calibrate.c) in the app to perform touch screen calibration by GUI tool instead of terminal command line console.

## file structure

| directory | description |
| -------------------------------- | ------------------------------------------------------------ |
| [android-9.0.0_r33](./android-9.0.0_r33) | Porting [tslib-1.20](./tslib-1.20) to [aosp](https://source.android.com/setup/build/downloading) [android-9.0.0_r33](./android-9.0.0_r33) codebase of vendor platform, take rk3399 as an example. |
| [tslib-1.20](./tslib-1.20)       | Fork from original [libts/tslib](https://github.com/libts/tslib) project, use the release version tslib-1.20. |
