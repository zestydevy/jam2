del /S *.c
del /S *.h
for /f "usebackq delims=|" %%f in (`dir /b "C:\Users\MDR\Desktop\mksprite64\dist\Debug\MinGW-Windows"`) do start mksprite64.exe -f %%f -p t -sx 1.0 -sy 1.0 -m 16
pause