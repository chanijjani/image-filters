# get script path
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# get image and rename
wget https://www.nasa.gov/images/content/569718main_fd3predock_full.jpg --directory-prefix=${SCRIPT_DIR} --quiet
mv ${SCRIPT_DIR}/569718main_fd3predock_full.jpg ${SCRIPT_DIR}/4k.jpg

# convert to BMP
convert ${SCRIPT_DIR}/4k.jpg ${SCRIPT_DIR}/4k.bmp
rm ${SCRIPT_DIR}/4k.jpg

# resize BMP image
convert ${SCRIPT_DIR}/4k.bmp -resize 1920x1080 ${SCRIPT_DIR}/fullhd.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 640x480 ${SCRIPT_DIR}/vga.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 88x66 ${SCRIPT_DIR}/sqcif.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 48x36 ${SCRIPT_DIR}/sim_fast.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 88x66 ${SCRIPT_DIR}/sim.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 176x132 ${SCRIPT_DIR}/qcif.bmp
convert ${SCRIPT_DIR}/4k.bmp -resize 352x264 ${SCRIPT_DIR}/cif.bmp
