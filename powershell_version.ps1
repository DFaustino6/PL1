$files = Get-ChildItem "inputs\" -Filter *.txt
foreach ($file in $files){
    $outfile = "results\" + $file.BaseName + $file.Extension
    for ($i = 0;$i -lt 31; $i++) {
        $file_p = "inputs\"+$file
        $result = Measure-Command { Invoke-Expression ".\seq.exe $file_p" } | findstr -i TotalMilliseconds
        Write-Output $result >> $outfile
    }
}
