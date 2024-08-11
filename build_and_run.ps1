param([bool]$RunAfterBuild = $true)

$CurrentDir = (Get-Location).ToString()
$StaticLibName = "fresh_lib.lib"
$ExampleExeName = "editor.exe"

function Exit-WithOptionalError {
  param($Msg = "")
  if((Get-Location).ToString() -ne $CurrentDir) {
    Set-Location -Path ".."
  }
  Remove-Item -Path "build" -Recurse -Force -ErrorAction SilentlyContinue
  if(-Not([string]::IsNullOrEmpty($Msg))) {
    Write-Host "Error: $Msg!" -ForegroundColor Red
    exit 1
  }
  exit 0
}

if(Test-Path "build") {
  Remove-Item -Path "build" -Recurse -Force -ErrorAction SilentlyContinue
}
if(Test-Path $ExampleExeName) {
  Remove-Item -Path $ExampleExeName -Force
}

New-Item -Path "build" -ItemType Directory
Set-Location -Path "build"

cmake -DCMAKE_CXX_FLAGS="/D__FRESH_DEBUG /D__FRESH_ENABLE_EDITOR" -DCMAKE_CONFIGURATION_TYPES=Release -G "Visual Studio 17 2022" ..

if($LASTEXITCODE -ne 0) {
  Exit-WithOptionalError -Msg "CMake failed to generate"
}

msbuild.exe fresh.sln /p:Configuration=Release /m

if($LASTEXITCODE -ne 0) {
  Exit-WithOptionalError -Msg "MSBuild failed"
}
if(Test-Path "Release/$StaticLibName") {
  Copy-Item -Path "$((Get-Location).ToString())/Release/$StaticLibName" -Destination "$CurrentDir/$StaticLibName" -Force
}
if(-Not(Test-Path "$CurrentDir/$StaticLibName")) {
  Exit-WithOptionalError -Msg "Cannot copy $((Get-Location).ToString())/Release/$StaticLibName to $CurrentDir/$StaticLibName"
}
if(-Not(Get-Command "elite" -ErrorAction SilentlyContinue)) {
  Exit-WithOptionalError -Msg "Cannot find Elite to build example program"
}

Set-Location -Path $CurrentDir
elite Elitefile only_example

if($LASTEXITCODE -ne 0) {
  Exit-WithOptionalError -Msg "Elite failed to build"
}
if(-Not(Test-Path $ExampleExeName)) {
  Exit-WithOptionalError -Msg "Cannot find $ExampleExeName to execute"
}
if($RunAfterBuild -eq $true) {
  Invoke-Expression "./$ExampleExeName"
}

Exit-WithOptionalError