#pragma once

typedef enum mode_e{
  bluetooth,
  hardwareTest,
  obstacleAvoid,
  obstacleFollow
} mode_t;

void    setupModeSelector();
mode_t  getMode();
