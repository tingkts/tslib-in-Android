# android-9.0.0_r33/aosp_r33
Porting [tslib-1.20](https://github.com/libts/tslib) to [aosp](https://source.android.com/setup/build/downloading) [android-9.0.0_r33](https://source.android.com/setup/start/build-numbers#source-code-tags-and-builds) codebase of the specified vendor platform, take rk3399 as an example.

```
$ repo init -u https://android.googlesource.com/platform/manifest -b android-4.0.1_r1
```


## Patch description


| git project (.git)       | patch | description |
| -------------------------- | ------ | ------------------------------------------------------------ |
| [external/tslib](./external/tslib) | [0001-porting-tslib-into-android](./external/tslib/0001-porting-tslib-into-android.patch)     | put [tslib](./../../tslib-1.20) into external/tslib, make it's able to build with android cross-complier build chain. |
| [frameworks/base](./frameworks/base)      | [0001-ts_calibrate-launcher-TsCalibrator.patch](./frameworks/base/0001-ts_calibrate-launcher-TsCalibrator.patch) | implement app TsCalibrator as ts_calibrate launcher. |
| [device/rockchip/rk3399](./device/rockchip/rk3399) | [0001-include-tslib-modules.patch](./device/rockchip/rk3399/0001-include-tslib-modules.patch) | include modules of [tslib](./external/tslib.zip) and [TsCalibrator](./frameworks/base/packages.zip) into system image. |
| [system/core](./system/core)  |  [0001-init-service-ts_calibrate.patch](./system/core/0001-init-service-ts_calibrate.patch) | define init service ts_calibrate, let it act as an init property service. |
| [device/rockchip/common](./device/rockchip/common)  |  [0001-sepolicy-of-ts_calibrate.patch](./device/rockchip/common/0001-sepolicy-of-ts_calibrate.patch) | define seplocy of init service ts_calibrate, let it pass the rules of SEPolicy of SELinux. |
| [frameworks/base](./frameworks/base)  |  [0002-apply-ts_calibrate-parameters.patch](./frameworks/base/0002-apply-ts_calibrate-parameters.patch) | apply calibration of affine transfrom from the output parameters of ts_calibrate. |
| [frameworks/native](./frameworks/native)  |  [0001-append-descriptor-of-input-device-into-dump-info.patch](./frameworks/native/0001-append-descriptor-of-input-device-into-dump-info.patch) | append descriptor of input device into dump info. |

