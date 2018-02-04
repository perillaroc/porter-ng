# porter-ng

A simple data conversion tool which converts GrADS binary data to GRIB 2 data.
It is currently tested on numerical weather prediction model's output 
produced by NWPC (Numerical Weather Prediction Center of CMA).

## Requirements

porter-ng uses ecCodes by ECMWF to encode GRIB 2 data. 
So please build and install ecCodes before building porter-ng.

porter-ng uses some libraries of Boost C++ library to parse GrADS data description file 
and command line arguments:

* system
* file system
* data time
* program options

porter-ng's config file is written in YAML. And yaml-cpp is used to parse YAML file.

## Installation

Use CMake to build from source code. Such as:

Some Cmake variable are available to set libraries' path.

* `ECCODES_INSTALL_PREFIX`: ecCodes's install prefix, default is `/usr/local`.
* `YAMLCPP_INSTALL_PREFIX`: yaml-cpp's install prefix, default is `/usr/local`.

## Getting Started

Use command line tool `porter` to convert GrADS data to GRIB 2.

```
porter --config=config.yaml \
    --output=output.grib2 \
    data.ctl
```

A simple config file:

```yaml
params:
  -
      name: t
      keys:
        # param
        discipline: 0
        parameterCategory: 0
        parameterNumber: 0

        # level
        typeOfLevel: isobaricInPa

  -
    name: u
    levels: [1000, 962.5]
    keys:
      # param
      discipline: 0
      parameterCategory: 2
      parameterNumber: 2

      # level
      typeOfLevel: isobaricInPa
```

## License

This project is licensed under the MIT License.

