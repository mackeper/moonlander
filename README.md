
## Setup container
### Powershell
Set-Variable container_name "qmk"
docker build -t $container_name .
docker container create -t --name $container_name $container_name
docker container start $container_name

## Usage
Set-Variable container_name "qmk"
Set-Variable source (Get-Childitem -Recurse -Include *_source | Select-Object -first 1)
Set-Variable source_path $source.FullName
Set-Variable source_name $source.Name
Set-Variable layout_name $source_name
Set-Variable keyboard "moonlander"
docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps
docker exec -it $container_name mkdir /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name
docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps
docker cp $source_path/. "${container_name}:/root/qmk_firmware/keyboards/moonlander/keymaps/${layout_name}"
docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name
docker exec -it $container_name qmk compile -kb $keyboard -km $layout_name
docker exec -it $container_name rm -r /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name
docker cp "${container_name}:/root/qmk_firmware/${keyboard}_${layout_name}.bin" .
docker exec -it $container_name rm /root/qmk_firmware/${keyboard}_${layout_name}.bin
