# Node.js mt19937_64 (V8 C++ addon)
## Mersenne Twister 19937 Generator (64 bit)
A Mersenne Twister pseudo-random generator of 64-bit numbers with a state size of 19937 bits.
(http://www.cplusplus.com/reference/random/mt19937_64/)

---

Dead-simple and minimal V8 C++ addon for major versions of Node.js (tested on 10+) to work with Mersenne Twister random generator.
Includes TypeScript typings.

## Installation

```bash
npm install https://github.com/Irelynx/node-mt19937_64

# or 

git clone https://github.com/Irelynx/node-mt19937_64
cd ./myNodejsApp
npm install ../node-mt19937_64
```

## Usage

```javascript
// 1. import (CommonJS)
const mt19937_64 = require('node-mt19937_64');
// { newFromSeed: [Function: newFromSeed] }

// 2. create generator
const generator = mt19937_64.newFromSeed(12345n);
// { next: [Function (anonymous)], seed: 12345n }

// 3. use next() to get next generator value
generator.next();
// 6597103971274460346n
```

### Generator creation

```javascript
// number as 1st argument
const generator = mt19937_64.newFromSeed(12345);
// { next: [Function (anonymous)], seed: 12345n }

// bigint as 1st argument
const generator = mt19937_64.newFromSeed(12345n);
// { next: [Function (anonymous)], seed: 12345n }

// default seed value
const generator = mt19937_64.newFromSeed();
// { next: [Function (anonymous)], seed: 5489n }

// high precision timestamp as seed
const generator = mt19937_64.newFromSeed(true);
// { next: [Function (anonymous)], seed: 16449451947620306n }
// seed is current timestamp in "periods"
// info: http://www.cplusplus.com/reference/chrono/time_point/time_since_epoch/

// other seed values
const generator = mt19937_64.newFromSeed(-1);
// { next: [Function (anonymous)], seed: 4294967295n }
const generator = mt19937_64.newFromSeed(1.75);
// { next: [Function (anonymous)], seed: 1n }
const generator = mt19937_64.newFromSeed(1e9);
// { next: [Function (anonymous)], seed: 1000000000n }
const generator = mt19937_64.newFromSeed(1e10);
// { next: [Function (anonymous)], seed: 1410065408n }
const generator = mt19937_64.newFromSeed(10n ** 10n);
// { next: [Function (anonymous)], seed: 10000000000n }
const generator = mt19937_64.newFromSeed(false);
// { next: [Function (anonymous)], seed: 5489n }

const generator = mt19937_64.newFromSeed(1, 2);
// Uncaught TypeError: Wrong number of arguments (0 or 1 expected - seed_orUseTimeAsSeed).

const generator = mt19937_64.newFromSeed(undefined);
const generator = mt19937_64.newFromSeed(null);
const generator = mt19937_64.newFromSeed("sick!");
const generator = mt19937_64.newFromSeed({});
const generator = mt19937_64.newFromSeed([]);
// Uncaught TypeError: Wrong argument 0 type. Number, BigInt or Boolean expected

```

## Verified versions of Node.js that works with addon

* Node.js v10.23.0 (V8 v6.8.275.32)
* Node.js v14.18.1 (V8 v8.4.371.23-node.84)

Tested at: 2022.02.15, on:
* Linux Ubuntu 20.04 (arm)
* Windows 10 (x64)

## Requirements

* g++ with C++ 11 support

## Available functions/variables

## Why yet another mt19937 module?

* **Major part of modules** in NPM or GitHub for mt19937 library **does not provide API to generate UInt64 numbers** or even **does not compile on newer versions of Node.js**, or developers refuse to support new versions of Node.js (because of V8 API changes, like "removing" v8::Handle<T>), or projects are completely abandoned
* Practice

## Used links and documentations

* [Node.js C++ Addons (nodejs.org)](https://nodejs.org/api/addons.html)
* [V8 documentation for version 8.4.371, (Node.js v14.15) (v8docs.nodesource.com)](https://v8docs.nodesource.com/node-14.15/d2/dc3/namespacev8.html)
* [Getting started with embedding V8 (v8.dev)](https://v8.dev/docs/embed)
* [Source code of Native Abstractions for Node.js (github.com)](https://github.com/nodejs/nan)
