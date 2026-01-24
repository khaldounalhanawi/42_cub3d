```c
/*
 * ═══════════════════════════════════════════════════════════════════════════
 *                       CUB3D FUNCTION CALL HIERARCHY
 * ═══════════════════════════════════════════════════════════════════════════
 */

'main'                                  /* Entry point */
│
├── 'example_data'                      /* Creates temporary mock initialization data with test map */
│
├── 'init_system'                       /* Initializes MLX, window, and game state */
│   │
│   ├── 'init_input'                    /* Initializes all input flags to 0 */
│   ├── 'init_player'                   /* Sets up player position and orientation */
│   │   └── 'get_player_dir'            /* Sets direction vector based on N/S/E/W character */
│   ├── 'convert_arr_to_color'          /* Converts RGB array to hexadecimal color value */
│   ├── 'mlx_init'                      /* MLX: Initializes graphics system */
│   ├── 'mlx_new_window'                /* MLX: Creates game window */
│   ├── 'load_textures'                 /* Loads all wall textures from XPM files */
│   │   ├── 'init_texture' × 4          /* Loads North, South, East, West wall textures */
│   │   │   ├── 'mlx_xpm_file_to_image' /* MLX: Loads XPM texture file */
│   │   │   └── 'mlx_get_data_addr'     /* MLX: Gets pixel data pointer */
│   │   ├── 'clear_data' [on error]     /* Frees initialization data */
│   │   │   └── 'clear_map'             /* Frees map grid memory */
│   │   └── 'clean_system_exit' [error] /* Cleanup and exit on failure */
│   └── 'init_frame'                    /* Creates the main rendering frame buffer */
│       ├── 'mlx_new_image'             /* MLX: Creates frame buffer image */
│       └── 'mlx_get_data_addr'         /* MLX: Gets frame pixel data pointer */
│
├── 'clear_data'                        /* Frees initialization data after system is ready */
│   └── 'clear_map'                     /* Frees map grid memory */
│
├── 'set_hooks'                         /* Registers all event handlers for the game */
│   ├── 'mlx_hook' × 3                  /* MLX: Registers three event handlers */
│   │   ├── 'close_window'              /* Handles window close event (X button) */
│   │   │   └── 'clean_system_exit'     /* Final cleanup and exit */
│   │   ├── 'key_press'                 /* Sets input flags when keys are pressed (W/S/A/D/Arrows) */
│   │   └── 'key_release'               /* Clears input flags when keys are released */
│   └── 'mlx_loop_hook'                 /* MLX: Registers the main game loop function */
│       └── 'update_and_render'         /* Called every frame automatically */
│           ├── 'update_position'       /* Checks input flags and updates player position/rotation */
│           │   ├── 'move_forward'      /* Collision check and move player forward */
│           │   ├── 'move_backward'     /* Collision check and move player backward */
│           │   ├── 'move_left'         /* Collision check and strafe player left */
│           │   ├── 'move_right'        /* Collision check and strafe player right */
│           │   ├── 'rot_left'          /* Rotate player view counterclockwise */
│           │   └── 'rot_right'         /* Rotate player view clockwise */
│           └── 'update_frame'          /* Creates new frame, renders, and displays it */
│               ├── 'mlx_new_image'     /* MLX: Creates new frame buffer */
│               ├── 'mlx_get_data_addr' /* MLX: Gets frame data pointer */
│               ├── 'my_mlx_pixel_put'  /* Draws player position and direction arrow */
│               ├── 'mlx_put_image_to_window' /* MLX: Displays frame to screen */
│               └── 'mlx_destroy_image' /* MLX: Destroys old frame to prevent memory leak */
│
├── 'mlx_loop'                          /* MLX: Starts infinite event loop until window is closed */
│
└── 'clean_system_exit'                 /* Final cleanup and program exit */
```
```c
/* ═══════════════════════════════════════════════════════════════════════════
 *                              EVENT FLOW DIAGRAM
 * ═══════════════════════════════════════════════════════════════════════════
 */

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER PRESSES KEY (W/A/S/D/Arrows)'                                     ║
╠══════════════════════════════════════════════════════════════════════════╣
║  key_press()                     /* Sets game->input flags to 1 */       ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER RELEASES KEY'                                                     ║
╠══════════════════════════════════════════════════════════════════════════╣
║  key_release()                   /* Sets game->input flags to 0 */       ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER CLOSES WINDOW (X button or ESC)'                                  ║
╠══════════════════════════════════════════════════════════════════════════╣
║  close_window()                  /* Triggers cleanup and exit */         ║
║    └── clean_system_exit()       /* Frees all resources and exits */     ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'EVERY FRAME (Automatic, ~60 FPS)'                                      ║
╠══════════════════════════════════════════════════════════════════════════╣
║  update_and_render()             /* Main game loop */                    ║
║    ├── update_position()         /* Processes input and moves player */  ║
║    └── update_frame()            /* Renders and displays new frame */    ║
╚══════════════════════════════════════════════════════════════════════════╝


/* ═══════════════════════════════════════════════════════════════════════════
 *                            MODULE ORGANIZATION
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  MAIN
 *    ./src/main.c                   Entry point and main program flow
 *    ./src/tester.c                 Mock data generation (temporary)
 *
 *  INITIALIZATION & CLEANUP
 *    ./src/utils/init_system.c      System and game initialization
 *    ./src/utils/init_player.c      Player position and direction setup
 *    ./src/utils/init_images.c      Texture and frame buffer loading
 *    ./src/utils/clean_system_exit.c Memory cleanup and exit handling
 *
 *  EVENT HANDLING & GAME LOOP
 *    ./src/hooks/set_hooks.c        Event handler registration
 *    ./src/hooks/controls.c         Keyboard input handlers
 *    ./src/hooks/actions_I.c        Movement functions (forward/backward/left/right)
 *    ./src/hooks/actions_II.c       Rotation functions (left/right)
 *    ./src/hooks/updates.c          Game loop and frame rendering
 *
 * ═══════════════════════════════════════════════════════════════════════════
 */
```
 * ═══════════════════════════════════════════════════════════════════════════
 */