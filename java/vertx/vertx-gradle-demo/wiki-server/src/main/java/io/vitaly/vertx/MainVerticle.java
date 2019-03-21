package io.vitaly.vertx;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;
import io.vertx.core.json.JsonObject;
import io.vertx.core.logging.LoggerFactory;
import io.vertx.ext.jdbc.JDBCClient;
import io.vertx.core.logging.Logger;

public class MainVerticle extends AbstractVerticle {
    private Future<Void> prepareDatabase() {
	Future<Void> future = Future.future();
	
	dbClient = JDBCClient.createShared(vertx, new JsonObject()
					   .put("url", "jdbc:hsqldb:file:db/wiki")
					   .put("driver_class", "org.hsqldb.jdbcDriver")
					   .put("max_pool_size", 30));

	dbClient.getConnection(ar -> {
		if (ar.failed()) {
		    LOGGER.error("Could not open a database connection", ar.cause());
		    future.fail(ar.cause());
		}
		});
	return future;
    }

    private Future<Void> startHttpServer() {
	Future<Void> future = Future.future();
	return future;
    }

    private JDBCClient dbClient;
    private static final Logger LOGGER = LoggerFactory.getLogger(MainVerticle.class);

    @Override
    public void start(Future<Void> startFuture) throws Exception {
	Future<Void> steps = prepareDatabase().compose(v -> startHttpServer());
	steps.setHandler(startFuture.completer());
    }
}
