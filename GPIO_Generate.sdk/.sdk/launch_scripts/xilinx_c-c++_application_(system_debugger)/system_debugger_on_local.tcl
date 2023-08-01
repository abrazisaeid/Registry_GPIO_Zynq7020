connect -url tcp:127.0.0.1:3121
source D:/All/Software/ZZ-Hardware/80-Vivado/01-PROJECT/002_GPIO_Generator/GPIO_Generate.sdk/gpio_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126"} -index 0
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126" && level==0} -index 1
fpga -file D:/All/Software/ZZ-Hardware/80-Vivado/01-PROJECT/002_GPIO_Generator/GPIO_Generate.sdk/gpio_wrapper_hw_platform_0/gpio_wrapper.bit
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126"} -index 0
loadhw -hw D:/All/Software/ZZ-Hardware/80-Vivado/01-PROJECT/002_GPIO_Generator/GPIO_Generate.sdk/gpio_wrapper_hw_platform_0/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126"} -index 0
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126"} -index 0
dow D:/All/Software/ZZ-Hardware/80-Vivado/01-PROJECT/002_GPIO_Generator/GPIO_Generate.sdk/gpio/Debug/gpio.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-HS2 2102599A2126"} -index 0
con
