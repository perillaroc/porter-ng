# porter-ng

A simple data conversion tool which converts GrADS binary data to GRIB 2 data.

It is currently tested on numerical weather prediction model's output data
produced by NWPC (Numerical Weather Prediction Center of CMA).

## Requirements

* [ecCodes](https://software.ecmwf.int/wiki/display/ECC/ecCodes+Home)

    porter-ng uses ecCodes by ECMWF to encode GRIB 2 data. 
    So please build and install ecCodes before building porter-ng.

* [Boost C++ libraries](http://www.boost.org/)

    porter-ng uses some libraries of Boost C++ libraries to parse GrADS data description file 
    and command line arguments:

    - system
    - file system
    - data time
    - program options

* [yaml-cpp](https://github.com/jbeder/yaml-cpp)

    porter-ng's config file is written in YAML. And yaml-cpp is used to parse YAML file.

* [muParser](https://github.com/beltoforion/muparser)

    porter-ng uses muParser to parse value expressions in config file.

## Installation

Use CMake to build from source code.

Some Cmake variables are available to help find required libraries. Such as:

* `ECCODES_INSTALL_PREFIX`: ecCodes's install prefix, default is `/usr/local`.
* `YAMLCPP_INSTALL_PREFIX`: yaml-cpp's install prefix, default is `/usr/local`.
* `MUPARSER_INSTALL_PREFIX`: muParser's install prefix, default is `/usr/local`.

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
    value: x + 273.15

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

Copyright &copy; 2018, Perilla Roc.

This project is licensed under [the MIT License](./LICENSE).
