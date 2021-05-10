#!/usr/bin/env -S npx ts-node
import * as fs from 'fs';
import { LLParse } from 'llparse';
import * as path from 'path';
import * as semver from 'semver';

import * as llsdp from '../src/llsdp';

const pkgFile = path.join(__dirname, '..', 'package.json');
const pkg = JSON.parse(fs.readFileSync(pkgFile).toString());

const BUILD_DIR = path.join(__dirname, '..', 'build');
const C_DIR = path.join(BUILD_DIR, 'c');
const SRC_DIR = path.join(__dirname, '..', 'src');

const C_FILE = path.join(C_DIR, 'llsdp.c');
const HEADER_FILE = path.join(BUILD_DIR, 'llsdp.h');

for (const dir of [ BUILD_DIR, C_DIR ]) {
  try {
    fs.mkdirSync(dir);
  } catch (e) {
    // no-op
  }
}

function build(mode: 'strict' | 'loose') {
  const llparse = new LLParse('llsdp__internal');
  const instance = new llsdp.SDP(llparse, mode);

  return llparse.build(instance.build().entry, {
    c: {
      header: 'llsdp',
    },
    debug: process.env.LLPARSE_DEBUG ? 'llsdp__debug' : undefined,
    headerGuard: 'INCLUDE_LLSDP_ITSELF_H_',
  });
}

function guard(strict: string, loose: string): string {
  let out = '';

  if (strict === loose) {
    return strict;
  }

  out += '#if LLSDP_STRICT_MODE\n';
  out += '\n';
  out += strict + '\n';
  out += '\n';
  out += '#else  /* !LLSDP_STRICT_MODE */\n';
  out += '\n';
  out += loose + '\n';
  out += '\n';
  out += '#endif  /* LLSDP_STRICT_MODE */\n';

  return out;
}

const artifacts = {
  loose: build('loose'),
  strict: build('strict'),
};

let headers = '';

headers += '#ifndef INCLUDE_LLSDP_H_\n';
headers += '#define INCLUDE_LLSDP_H_\n';

headers += '\n';

const version = semver.parse(pkg.version)!;

headers += `#define LLSDP_VERSION_MAJOR ${version.major}\n`;
headers += `#define LLSDP_VERSION_MINOR ${version.minor}\n`;
headers += `#define LLSDP_VERSION_PATCH ${version.patch}\n`;
headers += '\n';

headers += '#ifndef LLSDP_STRICT_MODE\n';
headers += '# define LLSDP_STRICT_MODE 0\n';
headers += '#endif\n';
headers += '\n';

const cHeaders = new llsdp.CHeaders();

headers += guard(artifacts.strict.header, artifacts.loose.header);

headers += '\n';

headers += cHeaders.build();

headers += '\n';

headers += fs.readFileSync(path.join(SRC_DIR, 'native', 'api.h'));

headers += '\n';
headers += '#endif  /* INCLUDE_LLSDP_H_ */\n';

fs.writeFileSync(C_FILE,
  guard(artifacts.strict.c || '', artifacts.loose.c || ''));
fs.writeFileSync(HEADER_FILE, headers);
