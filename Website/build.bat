@setlocal
@echo off
pushd %~dp0

call yarn
call yarn build
pause

popd
@endlocal
