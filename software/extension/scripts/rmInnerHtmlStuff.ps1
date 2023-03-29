$filePath = $args[0]
$tempFile = "./temp.txt"
$regex = "^.*\.innerHTML\s*=.*"

# Create a temporary file to store the modified contents of the original file
New-Item $tempFile -ItemType File -Force | Out-Null

# Read the contents of the original file and filter out lines that match the regex
Get-Content $filePath | Where-Object { $_ -notmatch $regex } | Set-Content $tempFile

# Replace the original file with the modified file
Remove-Item $filePath
Rename-Item $tempFile -NewName $filePath