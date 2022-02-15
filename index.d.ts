declare namespace mt19937_64 {
    export interface Generator {
        next(): bigint;
        seed: bigint;
    }
    export function newFromSeed(seed_orUseTimeAsSeed?: number | bigint | boolean): Generator;
}

export = mt19937_64;
