# metadata
Metadata is the intermediate I/O data, passing the necessary parameters between the three processes TsCalibrator, ts_calibrate and system_server(*InputManagerService*) as IPC media.



## file

| file | content format | content description | accessor |
| --- | --- | --- | --- |
| [/data/system/tscalibrate/active_tsdevice](./device_rootdir/data/system/tscalibrate/active_tsdevice) | _path_,_rotation_,_descriptor_,_name_ | identify which touch screen is active, and record its 4 token, _path_, _rotation_, _descriptor_, _name_, that splitter is comma(_,_).   | _w_ : TsCalibrator<br/> _r_ : ts_calibrate / InputManagerService  |
| [/data/system/tscalibrate/*descriptor*_*rotation*](./device_rootdir/data/system/tscalibrate/fcb503119744c4d512130cd1b7ef1cbfa0a03c5f_0) | _xScale_ _xyMix_ _xOffset_ _yxMix_ _yScale_ _yOffset_ _divisor_ _xResolution_ _yResolution_ _rotation_ |   record 10 calibration parameters output by ts_calibrate, that splitter is space( ).    | _w_ : ts_calibrate<br />_r_ : InputManagerService |

```
console:/ # ls -alZ /data/system/tscalibrate/
total 6
drwxrwxrwx  2 system system u:object_r:tscalibrate_data_file:s0 3488 2019-09-19 04:46 .
drwxrwxr-x 19 system system u:object_r:system_data_file:s0      3488 2019-09-19 08:42 ..
-rw-rw-rw-  1 system system u:object_r:tscalibrate_data_file:s0   93 2019-09-19 08:25 active_tsdevice
-rwxrwxrwx  1 root   root   u:object_r:tscalibrate_data_file:s0   52 2019-09-19 08:26 fcb503119744c4d512130cd1b7ef1cbfa0a03c5f_0

console:/ # cat /data/system/tscalibrate/active_tsdevice
/dev/input/event2,0,fcb503119744c4d512130cd1b7ef1cbfa0a03c5f,Weida Hi-Tech CoolTouch® System

console:/ # cat /data/system/tscalibrate/fcb503119744c4d512130cd1b7ef1cbfa0a03c5f_0
7785 282 -8372352 33 4517 -5146848 65536 3840 2160 0
```

<br />


| file | content format | content description | accessor |
| --- | --- | --- | --- |
| [/data/system/input-manager-state.xml](./device_rootdir/data/system/input-manager-state.xml) | xml | calibration parameters persisted by [input manager service](http://androidxref.com/9.0.0_r3/xref/frameworks/base/services/core/java/com/android/server/input/PersistentDataStore.java), and  applied by [inputflinger](http://androidxref.com/9.0.0_r3/xref/frameworks/native/services/inputflinger/).  | _rw_ : InputManagerService |

```
console:/ # ls -alZ /data/system/input-manager-state.xml
-rw------- 1 system system u:object_r:system_data_file:s0 605 2019-09-19 08:26 /data/system/input-manager-state.xml

console:/ # cat  /data/system/input-manager-state.xml
<?xml version='1.0' encoding='utf-8' standalone='yes' ?>
<input-manager-state>
    <input-devices>
        <input-device descriptor="fcb503119744c4d512130cd1b7ef1cbfa0a03c5f">
            <calibration format="affine" rotation="0">
                <x_scale>0.11878967</x_scale>
                <x_ymix>0.0043029785</x_ymix>
                <x_offset>-127.75195</x_offset>
                <y_xmix>5.0354004E-4</y_xmix>
                <y_scale>0.06892395</y_scale>
                <y_offset>-78.53467</y_offset>
            </calibration>
        </input-device>
    </input-devices>
</input-manager-state>
```

<br />

## system property


| key       | value type | value | accessor | purpose |
| -------------------------- | ------ | ----- | --- | --- |
| persist.vendor.apply.tscalparam | string | unspecified<br />apply<br />done | _w_ : ts_calibrate<br />_rw_ : InputManagerService| control whether to command _InputManagerService_ to persisit ts_calibrate parameters for that _inputflinger_ can apply touch screen calibration(apply _AffineTransform_.). |


<br />

## reference
```
adb shell dumpsys input
```
>[dumpsys_input.txt](./dumpsys_input.txt)

```
INPUT MANAGER (dumpsys input)


Event Hub State:
  BuiltInKeyboardId: 2
  Devices:

    4: Weida Hi-Tech CoolTouch® System
      Classes: 0x80000014
      Path: /dev/input/event2
      Enabled: true
      Descriptor: fcb503119744c4d512130cd1b7ef1cbfa0a03c5f
      Location: usb-fe380000.usb-1.2/input0
      ControllerNumber: 0
      UniqueId:
      Identifier: bus=0x0003, vendor=0x2575, product=0x5130, version=0x0110
      KeyLayoutFile:
      KeyCharacterMapFile:
      ConfigurationFile:
      HaveKeyboardLayoutOverlay: false

Input Reader State:

  Device 4: Weida Hi-Tech CoolTouch® System
    Descriptor fcb503119744c4d512130cd1b7ef1cbfa0a03c5f
    Generation: 14
    IsExternal: true
    HasMic:     false
    Sources: 0x00001002
    KeyboardType: 0
    Motion Ranges:
      X: source=0x00001002, min=0.000, max=3839.000, flat=0.000, fuzz=0.000, resolution=24.727
      Y: source=0x00001002, min=0.000, max=2159.000, flat=0.000, fuzz=0.000, resolution=24.587
      PRESSURE: source=0x00001002, min=0.000, max=1.000, flat=0.000, fuzz=0.000, resolution=0.000
    Touch Input Mapper (mode - direct):
      Parameters:
        GestureMode: multi-touch
        DeviceType: touchScreen
        AssociatedDisplay: hasAssociatedDisplay=true, isExternal=true, displayId=''
        OrientationAware: true
      Raw Touch Axes:
        X: min=0, max=32767, flat=0, fuzz=0, resolution=211
        Y: min=0, max=32767, flat=0, fuzz=0, resolution=373
        Pressure: unknown range
        TouchMajor: unknown range
        TouchMinor: unknown range
        ToolMajor: unknown range
        ToolMinor: unknown range
        Orientation: unknown range
        Distance: unknown range
        TiltX: unknown range
        TiltY: unknown range
        TrackingId: min=0, max=65535, flat=0, fuzz=0, resolution=0
        Slot: min=0, max=9, flat=0, fuzz=0, resolution=0
      Calibration:
        touch.size.calibration: none
        touch.pressure.calibration: none
        touch.orientation.calibration: none
        touch.distance.calibration: none
        touch.coverage.calibration: none
      Affine Transformation:
        X scale: 0.123
        X ymix: 0.002
        X offset: -162.287
        Y xmix: 0.001
        Y scale: 0.068
        Y offset: -71.864
      Viewport: displayId=0, orientation=0, logicalFrame=[0, 0, 3840, 2160], physicalFrame=[0, 0, 3840, 2160], deviceSize=[3840, 2160]
      SurfaceWidth: 3840px
      SurfaceHeight: 2160px
      SurfaceLeft: 0
      SurfaceTop: 0
      PhysicalWidth: 3840px
      PhysicalHeight: 2160px
      PhysicalLeft: 0
      PhysicalTop: 0
      SurfaceOrientation: 0
      Translation and Scaling Factors:
        XTranslate: 0.000
        YTranslate: 0.000
        XScale: 0.117
        YScale: 0.066
        XPrecision: 8.533
        YPrecision: 15.170
        GeometricScale: 0.092
        PressureScale: 0.000
        SizeScale: 0.000
        OrientationScale: 0.000
        DistanceScale: 0.000
        HaveTilt: false
        TiltXCenter: 0.000
        TiltXScale: 0.000
        TiltYCenter: 0.000
        TiltYScale: 0.000
      Last Raw Button State: 0x00000000
      Last Raw Touch: pointerCount=0
      Last Cooked Button State: 0x00000000
      Last Cooked Touch: pointerCount=0
      Stylus Fusion:
        ExternalStylusConnected: false
        External Stylus ID: -1
        External Stylus Data Timeout: 9223372036854775807
      External Stylus State:
        When: 9223372036854775807
        Pressure: 0.000000
        Button State: 0x00000000
        Tool Type: 0
```
