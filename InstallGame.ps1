# InstallGame.ps1

# URL to the game zip file
$gameUrl = "https://github.com/YuvalHasson/oop2_The_Legend_of_Zelda/releases/download/%23zeldaClone/x64-Release.zip"

# Paths
$documentsFolder = [System.Environment]::GetFolderPath("MyDocuments")
$output = [System.IO.Path]::Combine($documentsFolder, "ZeldaClone.zip")
$extractPath = [System.IO.Path]::Combine($documentsFolder, "ZeldaClone")
$desktop = [System.Environment]::GetFolderPath("Desktop")
$exePath = "$extractPath\x64-Release\oop2_project.exe"

# Download the game zip file
Invoke-WebRequest -Uri $gameUrl -OutFile $output

# Extract the game
Expand-Archive -Path $output -DestinationPath $extractPath

# Create a shortcut on the Desktop
$shortcutPath = [System.IO.Path]::Combine($desktop, "ZeldaClone.lnk")
$wsh = New-Object -ComObject WScript.Shell
$shortcut = $wsh.CreateShortcut($shortcutPath)
$shortcut.TargetPath = $exePath
$shortcut.WorkingDirectory = [System.IO.Path]::GetDirectoryName($exePath)
$shortcut.Save()

# Run the game
# Start-Process -FilePath $exePath