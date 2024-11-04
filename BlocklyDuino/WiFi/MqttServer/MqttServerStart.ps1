# 檢查是否以管理員身份運行
If (-Not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator"))
{
    # 如果不是管理員，則重新啟動 PowerShell 並以管理員身份運行
    $newProcess = New-Object -TypeName System.Diagnostics.ProcessStartInfo
    $newProcess.FileName = "powershell"
    $newProcess.Arguments = "-NoProfile -ExecutionPolicy Bypass -File `"" + $PSCommandPath + "`""
    $newProcess.Verb = "runas"
    [System.Diagnostics.Process]::Start($newProcess)
    Exit
}

# 執行你的腳本內容
$executable = "C:\Program Files\mosquitto\mosquitto.exe"
$config = "C:\Program Files\mosquitto\mosquitto.conf"

& "$executable" -c "$config" -v

Read-Host "Press Enter to exit"
