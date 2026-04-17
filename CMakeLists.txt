cmake_minimum_required(VERSION 3.25)

# Nombre de tu proyecto
project(RatedLayoutsMod)

# Busca el SDK de Geode (el que GitHub descargará automáticamente)
find_package(Geode REQUIRED)

# Configuración del Mod
add_geode_mod(
    ${PROJECT_NAME}
    # Archivos de código (asegúrate de que tu archivo se llame main.cpp y esté en la carpeta src)
    SOURCES 
        src/main.cpp
    
    # Si añades imágenes (.png) o sonidos (.ogg), ponlos en una carpeta llamada 'resources'
    # y descomenta la línea de abajo:
    # RESOURCES resources/
)

# Esto es opcional pero recomendado: ayuda a organizar los archivos en editores
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Mods")
