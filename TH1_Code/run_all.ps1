# Script bien dich va chay toan bo cac vi du thuc hanh OpenMP TH1
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH

Write-Host "==========================================================" -ForegroundColor Cyan
Write-Host "   HE THONG THUC HANH LAP TRINH SONG SONG OPENMP - TH1   " -ForegroundColor Cyan
Write-Host "==========================================================" -ForegroundColor Cyan

$files = Get-ChildItem -Filter "*.c" | Sort-Object Name

foreach ($file in $files) {
    $exeName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name) + ".exe"
    Write-Host "`n>>> DANG BIEN DICH: $($file.Name)..." -ForegroundColor Yellow
    gcc -fopenmp $file.Name -o $exeName
    if ($LASTEXITCODE -eq 0) {
        Write-Host ">>> KET QUA CHAY ($exeName):" -ForegroundColor Green
        & ".\$exeName"
    } else {
        Write-Host "Loi bien dich $file.Name" -ForegroundColor Red
    }
}
