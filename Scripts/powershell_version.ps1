$files = Get-ChildItem "..\inputs\" -Filter *.txt
foreach ($file in $files){
    $outfile = "..\results\th\" + $file.BaseName + $file.Extension
    for ($i = 0;$i -lt 31; $i++) {
        $file_p = "..\inputs\"+$file
        $result = Measure-Command { Invoke-Expression "..\src\th.exe $file_p" } | findstr -i TotalMilliseconds
        Write-Output $result >> $outfile
    }
}

foreach ($file in $files){
    $outfile = "..\results\omp\" + $file.BaseName + $file.Extension
    for ($i = 0;$i -lt 31; $i++) {
        $file_p = "..\inputs\"+$file
        $result = Measure-Command { Invoke-Expression "..\src\opemp.exe $file_p" } | findstr -i TotalMilliseconds
        Write-Output $result >> $outfile
    }
}