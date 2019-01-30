fs = 8000; 

[key_num_0] = DTMF_signal_decoder(  tone_0, fs, 1)
[key_num_0_noisy] = DTMF_signal_decoder(  tone_0_noisy, fs, 1)

[key_num_1] = DTMF_signal_decoder(  tone_1, fs, 1)
[key_num_1_noisy] = DTMF_signal_decoder(  tone_1_noisy, fs, 1)

[key_num_2] = DTMF_signal_decoder(  tone_2, fs, 1)
[key_num_2_noisy] = DTMF_signal_decoder(  tone_2_noisy, fs, 1)

[key_num_3] = DTMF_signal_decoder(  tone_3, fs, 1)
[key_num_3_noisy] = DTMF_signal_decoder(  tone_3_noisy, fs, 1)

[key_num_4] = DTMF_signal_decoder(  tone_4, fs, 1)
[key_num_4_noisy] = DTMF_signal_decoder(  tone_4_noisy, fs, 1)

[key_num_5] = DTMF_signal_decoder(  tone_5, fs, 1)
[key_num_5_noisy] = DTMF_signal_decoder(  tone_5_noisy, fs, 1)

[key_num_6] = DTMF_signal_decoder(  tone_6, fs, 1)
[key_num_6_noisy] = DTMF_signal_decoder(  tone_6_noisy, fs, 1)

[key_num_7] = DTMF_signal_decoder(  tone_7, fs, 1)
[key_num_7_noisy] = DTMF_signal_decoder(  tone_7_noisy, fs, 1)

[key_num_8] = DTMF_signal_decoder(  tone_8, fs, 1)
[key_num_8_noisy] = DTMF_signal_decoder(  tone_8_noisy, fs, 1)

[key_num_9] = DTMF_signal_decoder(  tone_9, fs, 1)
[key_num_9_noisy] = DTMF_signal_decoder(  tone_9_noisy, fs, 1)

[key_num_no_tone_quiet] = DTMF_signal_decoder(  no_tone_quiet, fs, 1)
[key_num_no_tone_noisy] = DTMF_signal_decoder(  no_tone_noisy, fs, 1)
