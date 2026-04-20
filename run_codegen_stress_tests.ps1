$ErrorActionPreference = 'Continue'

$passTests = @(
  'test_codegen_stress_bubble12.snl',
  'test_codegen_stress_arr_record_chain.snl',
  'test_codegen_stress_proc_pipeline.snl'
)

$failTests = @(
  'test_codegen_stress_reject_call_type.snl',
  'test_codegen_stress_reject_index.snl'
)

Write-Host '===== PASS TESTS (expect semantic pass + codegen + Mars output) ====='
foreach ($t in $passTests) {
  Write-Host "\n>>> $t"
  .\parser.exe .\$t
  Write-Host '--- Mars run out.s ---'
  java -jar "Mars for Compile 2022.jar" nc out.s
}

Write-Host "\n===== FAIL TESTS (expect semantic fail, no codegen) ====="
foreach ($t in $failTests) {
  Write-Host "\n>>> $t"
  .\parser.exe .\$t
}
