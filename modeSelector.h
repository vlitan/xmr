#pragma once

typedef enum mode_e{
  bluetooth,
  hardwareTest,
  obstacleAvoid,
  mapRoom
} mode_t;

void    setupModeSelector();
mode_t  getMode();
