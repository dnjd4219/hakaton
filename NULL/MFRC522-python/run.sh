#!/bin/bash

echo `gnome-terminal -x sh -c "python SR501.py|less"`
echo `gnome-terminal -x sh -c "sudo python Read.py|less"`
echo `python app.py`
