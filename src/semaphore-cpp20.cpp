
// todo: examples?



// std::semaphore — limit concurrent access to N threads
// std::barrier — reusable count-down based synchronize threads in phases
    /* 
    All threads do their work, then all **wait at the barrier** until every thread arrives — then all resume together, repeating this each phase:
    ```
    phase 1:  th1 works...  th2 works...  th3 works...
                        [all arrive → barrier releases]
    ========================== BARRIER ================================== 
    phase 2:  th1 works...  th2 works...  th3 works...
                        [all arrive → barrier releases]
    ========================== BARRIER ================================== 
    phase 3: ...
    ```
    Like a checkpoint — nobody moves to the next phase until everyone finishes the current one.
    */

// std::latch — one-shot countdown, wait for N threads to finish
// - a barrier with one phase
    /* 
    main:    [waiting...]
    t1 done → count_down()   count: 3→2
    t2 done → count_down()   count: 2→1
    t3 done → count_down()   count: 1→0
    main:    [unblocked, continues] ✓
    // latch is now spent — cannot be reused 
    */
