import * as constants from './constants';
import { enumToMap, IEnumMap } from './utils';

type Encoding = 'none' | 'hex';

export class CHeaders {
  public build(): string {
    let res = '';

    res += '#ifndef LLLLSDP_C_HEADERS_\n';
    res += '#define LLLLSDP_C_HEADERS_\n';

    res += '#ifdef __cplusplus\n';
    res += 'extern "C" {\n';
    res += '#endif\n';

    res += '\n';

    const errorMap = enumToMap(constants.ERROR);
    const methodMap = enumToMap(constants.METHODS);
    const sdpMethodMap = enumToMap(constants.METHODS, constants.METHODS_SDP, [
      constants.METHODS.PRI,
    ]);
    const rtspMethodMap = enumToMap(constants.METHODS, constants.METHODS_RTSP);

    res += this.buildEnum('llsdp_errno', 'HPE', errorMap);
    res += '\n';
    res += this.buildEnum('llsdp_flags', 'F', enumToMap(constants.FLAGS),
      'hex');
    res += '\n';
    res += this.buildEnum('llsdp_lenient_flags', 'LENIENT',
      enumToMap(constants.LENIENT_FLAGS), 'hex');
    res += '\n';
    res += this.buildEnum('llsdp_type', 'SDP',
      enumToMap(constants.TYPE));
    res += '\n';
    res += this.buildEnum('llsdp_finish', 'SDP_FINISH',
      enumToMap(constants.FINISH));
    res += '\n';
    res += this.buildEnum('llsdp_method', 'SDP', methodMap);

    res += '\n';

    res += this.buildMap('SDP_ERRNO', errorMap);
    res += '\n';
    res += this.buildMap('SDP_METHOD', sdpMethodMap);
    res += '\n';
    res += this.buildMap('RTSP_METHOD', rtspMethodMap);
    res += '\n';
    res += this.buildMap('SDP_ALL_METHOD', methodMap);

    res += '\n';

    res += '#ifdef __cplusplus\n';
    res += '}  /* extern "C" */\n';
    res += '#endif\n';
    res += '#endif  /* LLLLSDP_C_HEADERS_ */\n';

    return res;
  }

  private buildEnum(name: string, prefix: string, map: IEnumMap,
                    encoding: Encoding = 'none'): string {
    let res = '';

    res += `enum ${name} {\n`;
    const keys = Object.keys(map);
    keys.forEach((key, i) => {
      const isLast = i === keys.length - 1;

      let value: number | string = map[key];

      if (encoding === 'hex') {
        value = `0x${value.toString(16)}`;
      }

      res += `  ${prefix}_${key.replace(/-/g, '')} = ${value}`;
      if (!isLast) {
        res += ',\n';
      }
    });
    res += '\n};\n';
    res += `typedef enum ${name} ${name}_t;\n`;

    return res;
  }

  private buildMap(name: string, map: IEnumMap): string {
    let res = '';

    res += `#define ${name}_MAP(XX) \\\n`;
    Object.keys(map).forEach((key) => {
      res += `  XX(${map[key]!}, ${key.replace(/-/g, '')}, ${key}) \\\n`;
    });
    res += '\n';

    return res;
  }
}
