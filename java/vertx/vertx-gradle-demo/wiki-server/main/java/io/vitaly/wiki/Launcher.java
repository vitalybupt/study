package io.vitaly.wiki;

import io.vertx.core.VertxOptions;
import io.vertx.core.json.JsonObject;
import io.vertx.core.metrics.MetricsOptions;

/**
 * This class is here so we can configure the metrics from the conf file.
 */
public class Launcher extends io.vertx.core.Launcher {
    private JsonObject metricsConfig = null;

    @Override
    public void afterConfigParsed(JsonObject config) {
        super.afterConfigParsed(config);
        metricsConfig = config.getJsonObject("metrics");
    }

    @Override
    public void beforeStartingVertx(VertxOptions options) {
        super.beforeStartingVertx(options);
        if (null != metricsConfig) {
            options.setMetricsOptions(
                    new MetricsOptions(metricsConfig)
            );
        }
    }

    public static void main(String[] args) {
        new Launcher().dispatch(args);
    }
}
