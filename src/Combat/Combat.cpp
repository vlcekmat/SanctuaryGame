#include "Combat.h"

CombatResult::CombatResult(const size_t & _playerCasualties, const size_t & _raiderCasualties): playerCasualties(_playerCasualties), raiderCasualties(_raiderCasualties){}

CombatResult Combat::evaluateCombat(size_t playerSoldiers, size_t raiderSoldiers) {
    CombatResult combatResult(0, 0);

    cout << "\nBATTLE: " << "player[" << playerSoldiers << "] vs raider[" << raiderSoldiers << ']' << endl;
    while(playerSoldiers > 0 && raiderSoldiers > 0){
        // battle round
        size_t coinFlip = rand() % 2;

        if (coinFlip == 1){
            // round won by the player
            cout << "Raiders took a casualty!" << endl;
            raiderSoldiers --;
            combatResult.raiderCasualties ++;
        }
        else if (coinFlip == 0){
            // round won by the raiders
            cout << "The player took a casualty!" << endl;
            playerSoldiers --;
            combatResult.playerCasualties ++;
        }
    }

    cout << "\nEnd of combat: " << endl;
    cout << " - player casualties: " << combatResult.playerCasualties << endl;
    cout << " - raider casualties: " << combatResult.raiderCasualties << endl;

    combatResult.remainingPlayer = playerSoldiers;
    combatResult.remainingRaider = raiderSoldiers;

    if (playerSoldiers > 0){
        // player won
        cout << "\033[1;32mTHE PLAYER WON THE BATTLE\033[0m\n" << endl;
    }
    else if (raiderSoldiers > 0){
        // raider won
        cout << "\033[1;31mRAIDERS WON THE BATTLE\033[0m\n" << endl;
    }
    else if (playerSoldiers == raiderSoldiers){
        // draw
        combatResult.draw = true;
        cout << "Everyone died. No one won here...\n" << endl;
    }

    return combatResult;
}