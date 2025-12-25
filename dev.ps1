# Simple build-and-run helper for Windows PowerShell
# Usage: pwsh ./dev.ps1

$ErrorActionPreference = 'Stop'

# Configure (idempotent)
cmake -S . -B build

# Build
cmake --build build

# Run (Debug target output path)
$exe = Join-Path -Path "build" -ChildPath "lms.exe"
if (!(Test-Path $exe)) {
    # fallback to default VC++ output (Debug) if generator places exe elsewhere
    $candidate = Join-Path -Path "build/Debug" -ChildPath "lms.exe"
    if (Test-Path $candidate) { $exe = $candidate }
}

if (!(Test-Path $exe)) {
    Write-Error "Executable not found after build: $exe"
}

& $exe
