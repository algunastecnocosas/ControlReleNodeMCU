# ControlReleNodeMCU
Control de relé doble con NodeMCU a través de una red wifi, con una web como interfaz de usuario.

Créditos y tutoriales de preparación:
1) Cómo funciona un módulo de dos relés con una Arduino: https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/
2) Caja 3D para un NodeMCU+módulo de 2 relés: https://www.thingiverse.com/thing:1867799/files de techniczny https://www.thingiverse.com/techniczny/designs
3) NodeMCU como servidor web: https://parzibyte.me/blog/2020/12/26/servidor-web-nodemcu-esp8266/
4) NodeMCU como AP y servidor web que controla el encendido de un LED: https://parzibyte.me/blog/2020/02/11/encender-apagar-led-wifi-nodemcu-esp8266/

Se aportan dos versiones:
1) El NodeMCU se conecta a una red wifi existente (hay que meter SSID y password en el programa). La IP asignada al NodeMCU se puede ver en el monitor serie. El NodeMCU actúa como servidor web. Conectándose desde un dispositivo conectado a esa wifi y poniendo esa IP en el navegador se pueden activar o desactivar ambos relés.
2) El NodeMCU actúa como AP, generando una wifi propia, de SSID "ControlReles" y contraseña "holacaracola". Conectándose desde un dispositivo conectado a esa wifi y poniendo en un navegador la dirección 192.168.1.1 , se pueden activar o desactivar ambos relés.

