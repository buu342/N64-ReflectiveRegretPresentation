@echo off
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_cart        -o mdl_n64_cart.h        -f mdl_n64_cart.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_cpu         -o mdl_n64_cpu.h         -f mdl_n64_cpu.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_heatsink    -o mdl_n64_heatsink.h    -f mdl_n64_heatsink.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_motherboard -o mdl_n64_motherboard.h -f mdl_n64_motherboard.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_ram         -o mdl_n64_ram.h         -f mdl_n64_ram.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_rcp         -o mdl_n64_rcp.h         -f mdl_n64_rcp.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_shellbot    -o mdl_n64_shellbot.h    -f mdl_n64_shellbot.S64
arabiki64.exe -q -t texturesdef.txt -n mdl_n64_shelltop    -o mdl_n64_shelltop.h    -f mdl_n64_shelltop.S64
pause