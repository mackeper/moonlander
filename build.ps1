function Log([string] $str) { Write-Host "[$(Get-Date -Format "HH:mm:ss")] " -NoNewline -Foreground Blue ; Write-Host "$str" }
function LogError([string] $str) { Write-Host "[$(Get-Date -Format "HH:mm:ss")] " -NoNewline -Foreground Blue ; Write-Host "$str" -Foreground Red }


function CreateOutputDir([string]$dir){
    mkdir -Force $dir
}

function Assert([Boolean]$condition, [string]$msg)
{
    if ($condition) { return }
    LogError $msg
    exit
}

function ValidateContainerRunning([string]$container_name)
{
    Assert ($null -ne $source) "source is missing value."
}

function CompileLayout([string]$container_name, [string]$layout_name, [string]$source_path, [string]$keyboard, [string]$bin_name)
{
    Log "Current keymaps:"
    docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps

    docker exec -it $container_name mkdir /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name

    Log "Current keymaps (new source should be added):"
    docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps

    docker cp $source_path/. "${container_name}:/root/qmk_firmware/keyboards/moonlander/keymaps/${layout_name}"

    Log "Source files in new keymap:"
    docker exec -it $container_name ls /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name

    docker exec -it $container_name qmk compile -kb $keyboard -km $layout_name
    docker exec -it $container_name rm -r /root/qmk_firmware/keyboards/moonlander/keymaps/$layout_name
    docker cp "${container_name}:/root/qmk_firmware/${bin_name}" .\bin\.
    docker exec -it $container_name rm /root/qmk_firmware/${keyboard}_${layout_name}.bin

    Log "Saved as: .\bin\${bin_name}"
}

function main
{
    $image_name = "qmk"
    $container_name = (docker ps -a -f ancestor=$image_name --format "{{.Names}}")
    $source = (Get-Childitem -Recurse -Include *_source | Select-Object -first 1)
    $source_path = $source.FullName
    $source_name = $source.Name.replace(' ', '_')
    $layout_name = $source_name.replace('_source', '')
    $keyboard = "moonlander"
    $bin_name = "${keyboard}_${layout_name}.bin"

    ValidateContainerRunning $container_name
    CreateOutputDir "bin"
    CompileLayout $container_name $layout_name $source_path $keyboard $bin_name
}

main
