#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''

'''

import numpy as np
import matplotlib.pyplot as plt

from modules.read_csv import read
import modules.filterlib as flt

# sampling frequency (how many samples per second)
fs = 250.0

# bandpass values
lowcut = 1.0
highcut = 50.0

# bandstop values
lowstop = 49.0
highstop = 51.0

# file with eeg data location
eeg_file = 'data/201506111703.csv'

# read the eeg file to array
data = read(eeg_file, delimiter=',', header=1)
data = [float(i[0]) for i in data]

# raw data from specified range
# rng_data = data[sec_begin*fs:sec_end*fs]

# required for futher plotting appropriate x axis (samples)
time_axis = range(len(data))

# plot raw signal
plt.plot(time_axis, data)
plt.show()

# filter data (using butt bandstop filter)
flted = flt.butter_bandstop_filter(data, lowstop, highstop, fs, order=2)
# filter data (using butt bandpass filter)
flted = flt.butter_bandpass_filter(flted, lowcut, highcut, fs, order=2)

# plot time domain of the signal
plt.plot(time_axis, flted)
plt.show()

# plot frequency domain of the signal
freq = abs(2 * np.fft.fft(flted))/len(data)
freq = freq[:fs]
plt.plot(freq)
plt.show()

# plot frequency domain of the signal
freq_all = abs(2 * np.fft.fft(data))/len(data)
plt.plot(freq_all)
plt.show()
