@echo off

cd %~dp0
call yarn
call yarn build
pause
